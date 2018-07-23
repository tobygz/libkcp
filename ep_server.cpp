#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "sessServer.h"


bool g_run = true;

void onQuit(int sigval){
    printf("called onQuit sigval: %d\n", sigval);
    if(sigval == SIGINT || sigval == SIGQUIT ) {
        g_run = false;
    }

}


inline unsigned int currentMs() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (unsigned int)((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int main(){

    signal(SIGINT, onQuit);
    signal(SIGQUIT, onQuit);

    //for listen socket
    //char* port = (char*)"6010";
    const int kcpPort = 20020;
    pthread_t idKcp = UDPListen::m_sInst->Listen(kcpPort);        

    unsigned int ms = currentMs();
    while(1){
        if(!g_run){
            break;
        }
        ms = currentMs();
        UDPListen::m_sInst->Update(ms);        
        usleep(1000);
    }

    UDPListen::m_sInst->Destroy();
    
    pthread_cancel(idKcp);    
    pthread_join(idKcp, NULL);
    return 0;
}

