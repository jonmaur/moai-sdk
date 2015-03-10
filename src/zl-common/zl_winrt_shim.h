#ifndef ZL_WINRT_SHIM_H
#define	ZL_WINRT_SHIM_H

//windows phone has no concept of current directory.
#define chdir zl_chdir	

#ifndef getenv
  #define getenv zl_winrt_getenv
#endif	

#undef getcwd
#ifndef getcwd
  #define getcwd zl_getcwd
#endif

#ifndef system
  #define system zl_winrt_system
#endif

#ifndef WaitForSingleObject
#define WaitForSingleObject(handle,time) WaitForSingleObjectEx(handle,time,FALSE)
#endif

#ifndef CreateMutex
#define CreateMutex(sec, owner, name) CreateMutexEx(sec, name, (owner) ? 1 : 0, MUTEX_ALL_ACCESS)
#endif

#ifndef CreateEvent
#define CreateEvent(attr, manual, initial, name) CreateEventEx(attr, name, ((initial) ? 2 : 0)  + ((manual) ? 1 : 0) , EVENT_ALL_ACCESS)
#endif


#ifndef InitializeCriticalSection
#define InitializeCriticalSection(m) InitializeCriticalSectionEx(m,0,1)
#endif

#ifndef GetTickCount
#define GetTickCount (DWORD) GetTickCount64
#endif

#ifndef CreateFile
#define CreateFile zl_winrt_createfile
#endif

#ifndef _beginthreadex
#define _beginthreadex CreateThread
#endif

#ifndef WaitForMultipleObjects
#define WaitForMultipleObjects(count,handles,wait,ms) WaitForMultipleObjectsEx(count,handles,wait,ms,FALSE)
#endif

#ifndef TerminateThread
#define TerminateThread(handle,arg)  ((void)0)
#endif

#ifndef ExpandEnvironmentStrings
#define ExpandEnvironmentStrings(src,dest,size) ((void)0)
#endif

#ifdef  __cplusplus
  extern "C" {
#endif
	  typedef struct ZL_SECURITY_ATTRIBUTES {
		  unsigned long nLength;
		  void * lpSecurityDescriptor;
		  long bInheritHandle;
	  } ZL_SECURITY_ATTRIBUTES, *PZL_SECURITY_ATTRIBUTES, *LPZL_SECURITY_ATTRIBUTES;



extern int zl_winrt_system(const char *command);
  extern char *zl_winrt_getenv(const char *name);
  extern void * zl_winrt_createfile(const wchar_t *lpFileName,
									unsigned long dwDesiredAccess, 
									unsigned long dwShareMode,
									LPZL_SECURITY_ATTRIBUTES lpSecurityAttributes,
									unsigned long dwCreationDisposition,
									unsigned long dwFlagsAndAttributes,
									void *hTemplateFile
									);

#ifdef  __cplusplus
  }
#endif
#endif
