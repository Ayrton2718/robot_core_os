//
//  threadutil_locker.hpp
//  thread-util
//
//  Created by matsushita sena on 2020/04/21.
//  Copyright © 2020年 matsushita sena. All rights reserved.
//

#include "threadutil_locker.hpp"

namespace thread_util
{

locker::locker( void )
{ 
    if( pthread_mutex_init( &m_mutex, NULL ) != 0 )
    {
        perror( "pthread_mutex_init failed" );
    }
}

}

