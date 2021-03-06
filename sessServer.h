#ifndef KCP_SESS_H
#define KCP_SESS_H

#include "ikcp.h"
#include <sys/types.h>
#include <sys/time.h>
#include <map>
#include <queue>

#define READ_BUFF_SIZE 4*1024
#define BUFF_CACHE_SIZE 16*1024

using namespace std;

class UDPConn {
    ikcpcb *m_kcp;
    bool m_bRead;
    int m_conv;
    int m_fd;
    int m_pid;
    public:
    UDPConn(int fd, int epfd, int pid, char* buf, int len);
    int getfd(){ return m_fd;}
    int getpid(){ return m_pid;}
    int m_epollFd;
    //for kcp input
    unsigned char m_buf[READ_BUFF_SIZE];
    unsigned char m_cacheBuf[BUFF_CACHE_SIZE];
    int m_offset;

    void resetRead(){
        m_bRead = false;
    }
    void markRead(){
        m_bRead = true;
    }
    bool isMarkRead(){
        return m_bRead;
    }

    size_t Write(const char *buf, size_t sz);

    void Close();
    void OnRead();
    int OnDealMsg();
    void Update(unsigned int ms);
    private:

    static int out_wrapper(const char *buf, int len, struct IKCPCB *, void *user);
	static void writelog(const char *log, struct IKCPCB *kcp, void *user);
    // output udp packet
    ssize_t output(const void *buffer, size_t length);
};

class UDPListen {
    private:
        unsigned int m_listenPort;
        int m_epollFd;
        int m_servFd;
        struct sockaddr_in* m_pServaddr;

        map<int,UDPConn*> m_mapConn;
        queue<UDPConn*> m_readQueue;

        void processMsg(int clifd);
        void acceptConn();

        UDPConn *m_pSelfConn;
    public:
        static long g_sess_id;
        static UDPListen* m_sInst;
        UDPConn* createConn(int clifd, char* hbuf,int len); 
        int getServFd(){return m_servFd;}
        void delConn(int fd);
        void markRead(UDPConn*);
        pthread_t Listen(const int lport);
        static void* epThread(void*);
        int getEpfd(){return m_epollFd;}


        void Destroy();

        void Update(unsigned int ms);
};




#endif //KCP_SESS_H
