#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "csocket.h"

static int get_hostaddr(const char *name);

o3cw::CSocket::CSocket():o3cw::CInTimeObject::CInTimeObject()
{
    bzero (&addr, sizeof (addr));
    listener=-1;
    error=0;
    addr.sin_family = AF_INET;

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    rtv.tv_sec = 0;
    rtv.tv_usec = 0;

    wtv.tv_sec = 0;
    wtv.tv_usec = 0;
    socket_id=-1;
    GetTime(last_activity_time);
}

o3cw::CSocket::CSocket(int sock_id):o3cw::CInTimeObject::CInTimeObject()
{
    bzero (&addr, sizeof (addr));
    listener=-1;
    error=0;
    addr.sin_family = AF_INET;

    FD_ZERO(&rfds);
    FD_ZERO(&wfds);

    rtv.tv_sec = 0;
    rtv.tv_usec = 0;

    wtv.tv_sec = 0;
    wtv.tv_usec = 0;
    
    socket_id=sock_id;
    mlock.Lock();
    GetTime(last_activity_time);
    mlock.UnLock();

}

o3cw::CSocket::~CSocket()
{
    	if (listener!=-1)
		close(listener);
	if (socket_id!=-1)
		close(socket_id);
}

int o3cw::CSocket::Connect(const char *ip, int port)
{
    int result=0;;
    mlock.Lock();
    if (socket_id!=-1)
        close(socket_id);
    
    socket_id = socket (AF_INET, SOCK_STREAM, 0);
    addr.sin_port = htons (port);
    inet_aton (ip, &addr.sin_addr);
    error=0;
    int flags = fcntl(socket_id, F_GETFL, 0);
    if(fcntl(socket_id, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        /*
        * Не получилось...
        */
        result=-1;
    }
    else
    {
        int r=connect (socket_id, (struct sockaddr *) &addr, sizeof (addr));
        if (r!=0)
        {
           if(errno == EINPROGRESS)
            {
               /* Connection not ready yet */
            }
            else
            {
                /* Error occured */
                result=-2;

            }
        }

        //Waiting for a connection
        wtv.tv_sec = 10; wtv.tv_usec = 50;

        FD_ZERO(&wfds);
        FD_SET(socket_id, &wfds);
        int max_fd = socket_id;
        select(max_fd + 1, NULL, &wfds, NULL, &wtv);

        if(FD_ISSET(socket_id, &wfds) || FD_ISSET(socket_id, &rfds))
        {
            socklen_t err_len;
            int err=0;

            err_len = sizeof(err);
            if(getsockopt(socket_id, SOL_SOCKET, SO_ERROR, &err, &err_len) < 0 || err != 0)
            {
                result=-3;
            }
            else
            {
                /* Connection UP */
                result=0;
            }
        }
        else
        {
            result=-1;
        }
    }
    mlock.UnLock();
    return result;
}

int o3cw::CSocket::ConnectionTimeout()
{
    int result=0;
    
    mlock.Lock();
    long long now;
    GetTime(now);
    result=(int)(now-last_activity_time);
    mlock.UnLock();
    
    return result;
}

void o3cw::CSocket::ForceDown()
{
    mlock.Lock();
    if (socket_id!=-1)
    {
	shutdown(socket_id,SHUT_RDWR);
	close(socket_id);
	socket_id=-1;
    }
    mlock.UnLock();
}

int o3cw::CSocket::GetFD()
{
    mlock.Lock();
    int result=socket_id;
    if (listener!=-1)
        result=listener;
    mlock.UnLock();
    return result;
}

int o3cw::CSocket::Bind(int port, const char *interface)
{
    mlock.Lock();
    
    listener = socket (AF_INET, SOCK_STREAM, 0);
    int val=-1;
    if (setsockopt (listener, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof (val))!=0)
    {
        perror("setsockopt SO_REUSEADDR");
	mlock.UnLock();
	return -1;
    }


    addr.sin_port = htons (port);

    if (interface!=NULL)
    {
        addr.sin_addr.s_addr = (get_hostaddr(interface));
    }
    else
    {
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
    }

    if (bind (listener, (struct sockaddr *) &addr, sizeof (addr)) != 0)
    {
        //ERROR
        error=CRS_ERR_BIND;
        mlock.UnLock();
        return -1;
    }
    error=0;
    mlock.UnLock();
    return 0;
}


int o3cw::CSocket::Listen()
{
    mlock.Lock();
    if (listen (listener, 20) != 0)
    {
        //ERROR
        error=CRS_ERR_LISTEN;
        mlock.UnLock();
        return -1;
    }
    error=0;
    if (fcntl(listener, F_SETFL, O_NONBLOCK)!=0)
    {
        perror("fcntl O_NONBLOCK");
    }
    mlock.UnLock();
    return 0;
}

int o3cw::CSocket::Accept()
{
    int size=sizeof (addr);
    int result=-1;
    mlock.Lock();
    error=0;
    FD_ZERO(&rfds);
    FD_SET(listener, &rfds);
    rtv.tv_sec = 1;
    rtv.tv_usec = 0;
    socket_id = accept (listener, (struct sockaddr *) &addr, (socklen_t *) & size);
    if (socket_id==-1)
        error=CRS_ERR_ACCEPT;
    else
        result=socket_id;
    mlock.UnLock();
    return result;
}

int o3cw::CSocket::Receive(std::string &buff)
{
    return Receive(buff, -1);
}

int o3cw::CSocket::Receive(std::string &buff, float timeout)
{
    mlock.Lock();
    timeout=0;
    int result=0;
    if (socket_id==-1)
    {
            error=CRS_ERR_LOST;
            mlock.UnLock();
            return -1;
    }

    int sock_id=socket_id;
    error=0;
    int retval=0;
    if (timeout==-1)
        retval=1;
    else
    {
        timeval timeo;
        timeo.tv_sec = int(timeout);
        timeo.tv_usec = (timeout-(float)((int)timeout))*100000;

        fd_set rf;
        FD_ZERO(&rf);
        FD_SET(socket_id, &rf);
        
        int max_fd=socket_id+1;
        mlock.UnLock();
        retval=select(max_fd, &rf, NULL, NULL, &timeo);
        mlock.Lock();
        if (retval<0)
        {

    //        if (errno==EBADF) printf("В одном из наборов находится неверный файловый дескриптор.\n");
    //        if (errno==EINTR) printf("Был пойман незаблокированный сигнал.\n");
    //        if (errno==EINVAL) printf("n отрицательно.\n");
    //        if (errno==ENOMEM) printf("Функция select не смогла выделить участок памяти для внутренних таблиц.\n");
    //        error=CRS_ERR_LOST;
            mlock.UnLock();
            return -1;
        }
    }

    if (retval==1)
    {
        char msg_part[512];
        int err=recv(sock_id, msg_part,512,0);
        if (err>0)
        {
            GetTime(last_activity_time);
            buff.append(msg_part,err);
            result+=err;
        }
        else
            result=-1;
    }
    mlock.UnLock();
    
    return result;
}

int o3cw::CSocket::Send(const char *data, size_t size)
{
	if (data==NULL) return 0;
	mlock.Lock();
	if (socket_id==-1)
	{
		mlock.UnLock();
		return -1;
	}
        FD_ZERO(&wfds);
	FD_SET(socket_id, &wfds);
	
	wtv.tv_sec = 0;
	wtv.tv_usec = 10000;
	
	int retval=select(socket_id+1, NULL, &wfds, NULL, &wtv);
	if (retval <=0)
	{
		//ERROR OR TIMEOUT - NO DATA SEND
		error=CRS_ERR_SEND;
		mlock.UnLock();
		return -1;
	}
	int r=send(socket_id,data,size,0);
	mlock.UnLock();
	return r;
}

int o3cw::CSocket::Send(const char *message)
{
    return this->Send(message, strlen(message));
}

int o3cw::CSocket::Send(std::string &message)
{
    return this->Send(message.c_str(), message.length());
}

static int get_hostaddr(const char *name)
{
    struct hostent *he;
    int             res = -1;
    int             a1,a2,a3,a4;
    
    if (sscanf(name,"%d.%d.%d.%d",&a1,&a2,&a3,&a4) == 4)
        res = inet_addr(name);
    else
    {
        he = gethostbyname(name);
        if (he)
            memcpy(&res , he->h_addr , he->h_length);
    }
    return res;
}


int o3cw::CSocket::readmultiselect(std::queue<o3cw::CSocket *> &in_s_list, std::queue<o3cw::CSocket *> &out_s_list, int sec, int usec)
{
    fd_set rfds;
    struct timeval my_tv;
    my_tv.tv_sec = sec; my_tv.tv_usec = usec;
    int result=0;

    int max_fd = -1;
    FD_ZERO(&rfds);
    
    std::queue<o3cw::CSocket *> cache_list;
    
    while (in_s_list.size()>0)
    {
        o3cw::CSocket *pc_clnt=in_s_list.front();
        in_s_list.pop();
        if (pc_clnt!=NULL)
        {	
            int socket_id=pc_clnt->GetFD();
            if (socket_id>=0)
            {
                if(socket_id > max_fd)
                    max_fd = socket_id;

                FD_SET(socket_id, &rfds);
            }
            cache_list.push(pc_clnt);
        }
    }
    
    select(max_fd + 1, &rfds, NULL, NULL, &my_tv);
    
    //for (it=in_s_list.begin(); it<in_s_list.end(); it++)
    while (cache_list.size()>0)
    {
        o3cw::CSocket *pc_clnt=cache_list.front();
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
                    if (pc_clnt->ConnectionTimeout())
                    {
                        delete pc_clnt;
                    }
                    else
                    {
                        in_s_list.push(pc_clnt);
                    }
                }
            }
        }
    }

    return result;
}
