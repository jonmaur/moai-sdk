#include "zl_winrt_shim.h"
#include <windows.h>
int zl_winrt_system(const char *command) {
  return -1;
}

char *zl_winrt_getenv(const char *name) {
  return NULL;
}

HANDLE zl_winrt_createfile(LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPZL_SECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	) {

	CREATEFILE2_EXTENDED_PARAMETERS pCreateExParams = { 0 };

	pCreateExParams.lpSecurityAttributes = (LPSECURITY_ATTRIBUTES) lpSecurityAttributes;
	pCreateExParams.hTemplateFile = hTemplateFile;
	pCreateExParams.dwFileFlags = dwFlagsAndAttributes & 0xFFFF0000;
	pCreateExParams.dwFileAttributes = dwFlagsAndAttributes & 0x0000FFFF;

	return CreateFile2(lpFileName,
		dwDesiredAccess,
		dwShareMode,
		dwCreationDisposition, &pCreateExParams
		);
}