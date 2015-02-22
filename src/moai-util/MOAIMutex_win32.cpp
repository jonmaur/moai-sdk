// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#ifdef _WIN32

#include <moai-util/MOAIMutex_win32.h>

//================================================================//
// MOAIMutexImpl
//================================================================//

//----------------------------------------------------------------//
void MOAIMutexImpl::Init () {
}

//----------------------------------------------------------------//
void MOAIMutexImpl::Lock () {

	WaitForSingleObjectEx ( mMutexHandle, INFINITE, FALSE );
}

//----------------------------------------------------------------//
MOAIMutexImpl::MOAIMutexImpl () {
#if (WINAPI_PARTITION_APP)
	mMutexHandle = CreateMutexEx(NULL, NULL, 0, SYNCHRONIZE );
#else
	mMutexHandle = CreateMutex(NULL, FALSE, NULL );
#endif

	
	assert ( mMutexHandle );
}

//----------------------------------------------------------------//
MOAIMutexImpl::~MOAIMutexImpl () {

	CloseHandle ( mMutexHandle );
	mMutexHandle = NULL;
}

//----------------------------------------------------------------//
void MOAIMutexImpl::Unlock () {

	ReleaseMutex ( mMutexHandle );
}

#endif