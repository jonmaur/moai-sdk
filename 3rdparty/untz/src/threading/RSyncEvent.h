//
//  RSyncEvent.h
//  Part of UNTZ
//
//  Created by Robert Dalton Jr. (bob@retronyms.com) on 06/01/2011.
//  Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
//

#ifndef RSYNCEVENT_H_
#define RSYNCEVENT_H_

#include "Untz.h"

// Use Win or Posix
#ifdef WIN32
	#include <windows.h>
#else
    #ifdef __ANDROID__
        #define POSIX
    #endif
    #ifdef __APPLE__
        #define POSIX
    #endif
	#ifndef POSIX
		#warning POSIX will be used (but you did not define it)
	#endif
	#include <pthread.h>
#endif

class RSyncEvent
{
private:

#ifdef WIN32
	HANDLE mEvent;
#else
	pthread_mutex_t mMutex;
	pthread_cond_t mCondition;
#endif

public:
	
	RSyncEvent()
	{
#ifdef WIN32
		mEvent = CreateEventEx(NULL, NULL, 0, SYNCHRONIZE);
#else
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		pthread_mutex_init(&mMutex, &attr);
		pthread_mutexattr_destroy(&attr);
		pthread_cond_init(&mCondition, 0);
#endif
	}
		
	virtual ~RSyncEvent()
	{ 
#ifdef WIN32
		CloseHandle(mEvent);
#else
		pthread_mutex_unlock(&mMutex);
		pthread_mutex_destroy(&mMutex);
		pthread_cond_destroy(&mCondition);
#endif
	}

	void wait()
	{ 
#ifdef WIN32
#if WINAPI_PARTITION_APP
		WaitForSingleObjectEx(static_cast<HANDLE>(mEvent), INFINITE, FALSE);
#else
		WaitForSingleObject(static_cast<HANDLE>(mEvent), INFINITE);
#endif
#else
		pthread_mutex_lock(&mMutex);
		pthread_cond_wait(&mCondition, &mMutex);
		pthread_mutex_unlock(&mMutex);
#endif
	}
	
	void signal()
	{ 
#ifdef WIN32
        SetEvent(mEvent);
#else
		pthread_mutex_lock(&mMutex);
		pthread_cond_broadcast(&mCondition);
		pthread_mutex_unlock(&mMutex);
#endif
	}
	
	void reset()
	{ 
#ifdef WIN32
		ResetEvent(mEvent);
#else
#endif
	}
};

#endif