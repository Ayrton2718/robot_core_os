#include "threadutil_launcher.hpp"

void* launched_func(void* arg)
{
    void (*thread_func)(void) = (void (*)(void))arg;
    thread_func();
    return NULL;
}

namespace thread_util
{

Launcher::Launcher(void (*thread_func)(void))
{
    pthread_create(&this->m_thread, NULL, launched_func, thread_func);
}

}
