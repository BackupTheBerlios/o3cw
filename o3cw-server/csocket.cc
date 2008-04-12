#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

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
    last_activity_time=0;
    connection_timeout=-1;
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
    
    connection_timeout=-1;
}

o3cw::CSocket::~CSocket()
{
    	if (listener!=-1)
		close(listener);
	if (socket_id!=-1)
		close(socket_id);
}

bool o3cw::CSocket::ConnectionTimeout()
{
    bool result=false;
    mlock.Lock();
    if (connection_timeout>0)
    {
        long long now;
        GetTime(now);
        printf("now=%lli\n", now);
        printf("%i<%lli\n",connection_timeout,(now-last_activity_time));
        if (connection_timeout<(now-last_activity_time))
            result=true;
    }
    mlock.UnLock();
    return result;
}

void o3cw::CSocket::SetTimeout(int v)
{
    mlock.Lock();
    connection_timeout=v;
    mlock.UnLock();
}

void o3cw::CSocket::ForceDown()
{
    mlock.Lock();
    if (socket_id!=-1)
    {
	shutdown(socket_id,SHUT_RDWR);
        printf("socket_id=%i\n",socket_id);
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
        rtv.tv_sec = 1;
        rtv.tv_usec = 0;


        FD_ZERO(&rfds);
        FD_SET(socket_id, &rfds);


        retval=select(socket_id+1, &rfds, NULL, NULL, &rtv);
        printf("socket id=%i select=%i\n", socket_id, retval);
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
	FD_ZERO(&wfds);
	if (socket_id==-1)
	{
		mlock.UnLock();
		return -1;
	}
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
    fd_set rfds, wfds;
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
    
    printf ("select returns %i, max sock=%i\n", select(max_fd + 1, &rfds, NULL, NULL, &my_tv), max_fd);
    
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
