//
//  threadutil_locker.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#ifndef THREADUTIL_LOCKER_HPP
#define THREADUTIL_LOCKER_HPP

#include <stdio.h>
#include <pthread.h>

namespace thread_util
{

class locker
{
private:
    pthread_mutex_t m_mutex;

public:
    locker( void );

    inline void lock( void )
    {
        pthread_mutex_lock( &this->m_mutex );
    }
    
    inline bool trylock( void )
    {
        return pthread_mutex_lock( &this->m_mutex );
    }

    inline void unlock( void )
    {
        pthread_mutex_unlock( &this->m_mutex );
    }
    
    inline static void yield(void)
    {
        pthread_yield_np();
    }
};

}

#endif /*THREADUTIL_LOCKER_HPP*/
