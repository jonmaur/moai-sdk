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


#ifdef  __cplusplus
  extern "C" {
#endif

  extern int zl_winrt_system(const char *command);
  extern char *zl_winrt_getenv(const char *name);
  extern HANDLE zl_winrt_createmutex(LPSECURITY_ATTRIBUTES lpMutexAttributes,
	  BOOL bInitialOwner,
	  LPCTSTR lpName
	  );

#ifdef  __cplusplus
  }
#endif
#endif
