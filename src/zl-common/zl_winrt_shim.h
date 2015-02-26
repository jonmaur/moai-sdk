#ifndef ZL_WINRT_SHIM_H
#define	ZL_WINRT_SHIM_H

//windows phone has no concept of current directory.
#define chdir zl_chdir	

#ifndef getenv
  #define getenv zl_winrt_getenv
#endif	

#ifndef getcwd
  #define getcwd zl_getcwd
#endif

#ifndef system
  #define system zl_winrt_system
#endif
#endif

#ifdef  __cplusplus
  extern "C" {
#endif

  extern int zl_winrt_system(const char *command);
  extern char *zl_winrt_getenv(const char *name);

#ifdef  __cplusplus
  }
#endif
