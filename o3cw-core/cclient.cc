#include <stdlib.h>

#include "cclient.h"
#include "cuser.h"
#include "cconfig.h"
#include "error.h"

o3cw::CClient::CClient(): o3cw::CSocket::CSocket()
{
    user=NULL;
    trusted=false;
    message_left=0;
    head_starts=0;
    head_ends=0;
}

o3cw::CClient::CClient(int sock): o3cw::CSocket::CSocket(sock)
{
    user=NULL;
    trusted=false;
    message_left=0;
    head_starts=0;
    head_ends=0;
}

o3cw::CClient::~CClient()
{
    
}

int o3cw::CClient::SendGenericError(int error)
{
    printf("Sending error code %i to client.\n", error);
    return 0;
}

int o3cw::CClient::SendBody(std::string &data)
{
    char head[1024];
    snprintf(head,1024, "HEAD\nlength=%u\n\n",data.length());
    std::string to_send(head);
    to_send.append(data);
    return Send(to_send);
}

bool o3cw::CClient::Trusted()
{
    bool result=false;
    mlock.Lock();
    result=trusted;
    mlock.UnLock();
    return result;
}

int o3cw::CClient::Receive()
{
    return Receive(-1);
}
int o3cw::CClient::Receive(float timeout)
{
    int result=0;
    bool any_data_left=true;
    int receive=o3cw::CSocket::Receive(msgbuff, timeout);
    if (receive<=0)
        result=receive;
    else
    {
        while (any_data_left)
        {
            any_data_left=false;
            
            if (message_left<=0)
            {
                head_starts=msgbuff.find("HEAD");
                //if (head_starts!=std::string::npos && head.length()>0)
                if (head_starts!=std::string::npos)
                {
                    head_ends=msgbuff.find("\n\n",head_starts);
                    if (head_ends!=std::string::npos)
                    {
                        head_ends+=2;
                        if (head_starts!=std::string::npos)
                            head.append(msgbuff, head_starts, head_ends-head_starts);
                        else
                            head.append(msgbuff, 0, head_ends);
                        
                        /* Parsing values in head */
                        
                        /* Body size */
                        std::string msize;
                        if (0==o3cw::CConfig::SimpleParse(head.c_str(), "length=", "\n\n", msize))
                            message_left=atoi(msize.c_str());
                        
                        /* Delete head (and parse body) */
                        msgbuff.erase(0,head_ends);
                    }
                    else
                        head.append(msgbuff);
                }
                else
                    head.append(msgbuff);
            }

            if (message_left>0)
            {
                receive=msgbuff.length();
                size_t to_read=message_left;

                if (receive<message_left)
                {
                    to_read=receive;
                }
                else
                {
                    /* Full message received and there some data in socket left */
                    any_data_left=true;
                }

                body.append(msgbuff, 0, to_read);

                message_left-=to_read;
                receive-=to_read;
                msgbuff.erase(0, to_read);
            }
            else if (message_left==0)
            {
                std::string *h=new std::string(head);
                std::string *b=new std::string(body);
                if (h==NULL || b==NULL)
                    return O3CW_ERR_OUT_OF_MEM;

                heads.push(h);
                bodies.push(b);
                //printf("new message pushed [%s][%s]\n",h->c_str(), b->c_str());

                head.erase();
                body.erase();

                result=1;
            }
        }
        msgbuff.erase();
    }
    return result;
}

std::string *o3cw::CClient::GetStringFromQueue(std::queue<std::string *> &q)
{
    std::string *result=NULL;
    
    mlock.Lock();
    if (q.size()>0)
    {
        result=q.front();
        q.pop();
    }
    mlock.UnLock();
    
    return result; 
}

std::string *o3cw::CClient::GetHead()
{
    return GetStringFromQueue(heads);
}

std::string *o3cw::CClient::GetBody()
{
    return GetStringFromQueue(bodies);
}

int o3cw::CClient::readmultiselect(std::queue<o3cw::CClient *> &in_s_list, std::queue<o3cw::CClient *> &out_s_list, int sec, int usec)
{
    fd_set rfds, wfds;
    struct timeval my_tv;
    my_tv.tv_sec = sec; my_tv.tv_usec = usec;
    int result=0;

    int max_fd = -1;
    FD_ZERO(&rfds);
    
    std::queue<o3cw::CClient *> cache_list;
    
    while (in_s_list.size()>0)
    {
        o3cw::CClient *pc_clnt=in_s_list.front();
        in_s_list.pop();
        if (pc_clnt!=NULL)
        {	
            int socket_id=pc_clnt->GetFD();
            if (socket_id>=0)
            {
                if(socket_id > max_fd)
                    max_fd = socket_id;

                FD_SET(socket_id, &rfds);
                //printf("new sock %i\n", socket_id);
            }
            cache_list.push(pc_clnt);
        }
    }
    
    select(max_fd + 1, &rfds, NULL, NULL, &my_tv);
    
    //for (it=in_s_list.begin(); it<in_s_list.end(); it++)
    while (cache_list.size()>0)
    {
        o3cw::CClient *pc_clnt=cache_list.front();
        cache_list.pop();
        
        if (pc_clnt!=NULL)
        {
            int socket_id=pc_clnt->GetFD();
            if (socket_id>=0)
            {
                if (FD_ISSET(socket_id, &rfds))
                {
                    out_s_list.push(pc_clnt);
                    result++;
                }
                else
                {
/*                    if (pc_clnt->ConnectionTimeout())
                    {
                        printf("timeout!\n");
                        delete pc_clnt;
                    }
                    else*/
                    {
                        //printf("pushing back %i\n", pc_clnt->GetFD());
                        in_s_list.push(pc_clnt);
                    }
                }
            }
        }
    }

    return result;
}
