// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#ifdef _WIN32

#include <zl-util/ZLUnique.h>

#if (WINAPI_PARTITION_APP)		
#include <objbase.h>
#else
#pragma warning ( disable:4512 )
#pragma warning ( disable:4355 )

#include <kashmir/winrand.h>
#include <kashmir/uuid.h>
#endif
//================================================================//
// ZLUnique
//================================================================//

//----------------------------------------------------------------//
STLString ZLUnique::GetGUID () {
	std::stringstream buffer;
#if (WINAPI_PARTITION_APP)	
	GUID guid;
	char szGuid[40] = { 0 };

	CoCreateGuid(&guid);
	sprintf(szGuid, "{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}", guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
	buffer << szGuid;
#else
	kashmir::system::WinRand winrandom;
	
	
	kashmir::uuid_t uuid;
    
	winrandom >> uuid;
    buffer << uuid;
#endif
	return buffer.str ();

}

#endif
