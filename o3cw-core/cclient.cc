#include <stdlib.h>

#include "cclient.h"
#include "cuser.h"
#include "cconfig.h"
#include "error.h"
#include "cdoc.h"

o3cw::CClient::CClient(): o3cw::CSocket::CSocket()
{
    m_user=NULL;
    trusted=false;
    message_left=0;
    head_starts=0;
    head_ends=0;
    use_count=0;
}

o3cw::CClient::CClient(int sock): o3cw::CSocket::CSocket(sock)
{
    m_user=NULL;
    trusted=false;
    message_left=0;
    head_starts=0;
    head_ends=0;
    use_count=0;
}

o3cw::CClient::~CClient()
{
    std::vector <o3cw::CDoc *>::iterator search_it;
    for (search_it=opened_docs.begin(); search_it!=opened_docs.end(); search_it++)
    {
        (*search_it)->RemoveClientFromMulticast(*this);
    }
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
    //printf("%i byte(s) received: [%s]\n", receive, msgbuff.c_str());
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

int o3cw::CClient::OpenDoc(o3cw::CDoc &doc)
{
    mlock.Lock();
    printf(" * pushed doc into open\n");
    opened_docs.push_back(&doc);
    mlock.UnLock();
    return 0;
}

int o3cw::CClient::CloseDoc(o3cw::CDoc &doc)
{
    std::vector <o3cw::CDoc *>::iterator search_it;
    mlock.Lock();
    for (search_it=opened_docs.begin(); search_it!=opened_docs.begin(); search_it++)
    {
        if ((*search_it)==&doc)
        {
            (*search_it)->RemoveClientFromMulticast(*this);
            opened_docs.erase(search_it);
            mlock.UnLock();
            return 0;
        }
    }
    mlock.UnLock();
    return -1;
}

void o3cw::CClient::Use()
{
    mlock.Lock();
    use_count++;
    mlock.UnLock();
}

void o3cw::CClient::UnUse()
{
    mlock.Lock();
    use_count--;
    mlock.UnLock();
}

int o3cw::CClient::GetUseCount()
{
    int result;
    mlock.Lock();
    result=use_count;
    mlock.UnLock();
    return result;
}

int o3cw::CClient::FdGetMax(std::vector<o3cw::CClient *> &in_list)
{
    int max=-1;
    for (std::vector<o3cw::CClient *>::iterator it=in_list.begin(); it!=in_list.end(); it++)
    {
        int sock=(*it)->GetFD();
        if (sock>max)
            max=sock;
    }
    return max;
}

int o3cw::CClient::FdSetRemove(fd_set &read_fds, int &max_fd, std::vector<o3cw::CClient *> &in_list, o3cw::CClient &client)
{
    int socket=client.GetFD();
    if (socket==-1)
        return -1;
    printf("sock=%i\n",socket);
    FD_CLR(socket, &read_fds);
    if (socket==max_fd)
        max_fd=FdGetMax(in_list);
    return 0;
}

int o3cw::CClient::FdSetAdd(fd_set &read_fds, int &max_fd, std::vector<o3cw::CClient *> &in_list, o3cw::CClient &client)
{
    int socket=client.GetFD();
    if (socket==-1)
        return -1;
    printf("sock=%i\n",socket);
    FD_SET(socket, &read_fds);
    if (socket>max_fd)
        max_fd=socket;
    return 0;
}

int o3cw::CClient::FdSetCompile(fd_set &read_fds, std::vector<o3cw::CClient *> &in_list)
{
    int result=-1;
    FD_ZERO(&read_fds);
    std::vector<o3cw::CClient *>::iterator it;
    for (it=in_list.begin(); it!=in_list.end(); it++)
    {
        o3cw::CClient *pc_clnt=*it;
        if (pc_clnt!=NULL)
        {
            int socket_id=pc_clnt->GetFD();
            if (socket_id>=0)
            {
                if (socket_id>result)
                    result=socket_id;

                FD_SET(socket_id, &read_fds);
            }
        }
    }
    return result;
}

int o3cw::CClient::readmultiselect(fd_set &read_fds, int &max_fd, std::vector<o3cw::CClient *> &in_list, std::queue<std::vector <o3cw::CClient *>::iterator> &out_list, int sec, int usec)
{
    if (max_fd<0)
        return 0;
    struct timeval my_tv;
    my_tv.tv_sec = sec; my_tv.tv_usec = usec;
    int result=0;
    
    select(max_fd + 1, &read_fds, NULL, NULL, &my_tv);
    
    std::vector<o3cw::CClient *>::iterator it;
    
    for (it=in_list.begin(); it!=in_list.end(); it++)
    {
        o3cw::CClient *pc_clnt=*it;
        if (pc_clnt!=NULL)
        {
            int socket_id=pc_clnt->GetFD();
            if (socket_id>=0)
            {
                if (FD_ISSET(socket_id, &read_fds))
                {
                    out_list.push(it);
                    result++;
                    if (max_fd==socket_id)
                    {
                        
                    }
                    else
                    {
                        //FD_CLR(socket_id, read_fds);
                    }
                }
                else
                    FD_SET(socket_id, &read_fds);
            }
        }
    }
    return result;
}

int o3cw::CClient::SetUser(o3cw::CUser &user)
{
    mlock.Lock();
    m_user=&user;
    trusted=true;
    mlock.UnLock();
    return 0;
}

o3cw::CUser *o3cw::CClient::GetUser()
{
    o3cw::CUser *result=NULL;
    mlock.Lock();
    result=m_user;
    mlock.UnLock();
    return result;
}
