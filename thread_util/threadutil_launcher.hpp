#ifndef THREADUTIL_LAUNCHAR_HPP
#define THREADUTIL_LAUNCHAR_HPP

#include <stdio.h>
#include <stdint.h>

#include <pthread.h>

namespace thread_util
{

class Launcher
{
private:
    pthread_t   m_thread;
    int         m_status;
public:
    Launcher(void (*thread_func)(void));

    // size_t get_id(void);

    // static size_t get_myid(void);

    // static 
};

}

#endif /*THREADUTIL_LAUNCHAR_HPP*/