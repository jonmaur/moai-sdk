#include "pch.h"
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <thread>
#include <iostream>
#include <fstream>
#include "..\ms\vstemplates\winrtcomponent.h"
#define echo(A) OutputDebugStringA(A);OutputDebugStringA("\n");
typedef int (__cdecl *winrt_main)(int Argc, char *ARGV[]);
int errorlevel=0;

std::string LocalFolderFile(Platform::String^ file)
{
  auto path = Windows::Storage::ApplicationData::Current->LocalFolder->Path + "\\" + file;
  std::wstring tmp(path->Begin(), path->End());
  return std::string (tmp.begin(), tmp.end());
}

Platform::String^ charArrayToPlatformString(int argc, char **argv)
{
  Platform::String^ out = "";
  for (int i = 0; i < argc; i++)
  {
    std::string str(argv[i]);
    std::wstring wstr(str.begin(), str.end());
    out += ref new Platform::String(wstr.data(), wstr.length())+ " ";
  }
  return out;
}

void dynload(Platform::String^ modName, int argc, std::string* argv_const, winrtcomponent::testClass ^T)
{
  //Conversion from const char to char since openssl methods writes on these arguments...
  char **argv = NULL;
  HMODULE module = NULL;

  argv = new char*[argc];
  if (argv == NULL)
  {
    errorlevel = 1;
    goto cleanup;
  }
  memset(argv, 0, argc * sizeof(char*));

  for (int i = 0; i < argc; i++)
  {
    unsigned int l = argv_const[i].length();
    argv[i] = new char [l+1];
    if (argv[i] == NULL)
    {
      errorlevel = 1;
      goto cleanup;
    }

    for (unsigned j = 0; j < l; j++)
    {
      argv[i][j] = argv_const[i][j];
    }
    argv[i][l] = 0;
  }

  module = LoadPackagedLibrary(modName->Data(), 0);
  winrt_main pMain = (winrt_main) GetProcAddress(module, "winrt_main");
  if (!pMain)
  {
    errorlevel = 1;
    goto cleanup;
  }
  try
  {
    LARGE_INTEGER frequency, start, end;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);

    int errorcode = pMain(argc, argv);
    QueryPerformanceCounter(&end);

    double interval = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    errorlevel |= errorcode;
    T->updateRun(charArrayToPlatformString(argc, argv), errorcode, interval);
  }
  catch (Platform::Exception ^e)
  {
    errorlevel = 1;
  }

cleanup:
  if (module != NULL)
  {
    FreeLibrary(module);
  }
  for (int i = 0; i < argc; i++)
  {
    if (argv[i] != NULL)
    {
      delete []argv[i];
    }
  }
  delete []argv;
}

int winrtcomponent::testClass::test()

{
  FILE *pCout, *pCerr;
  freopen_s(&pCout, LocalFolderFile("openssl.test.stdout.log").c_str(), "w", stdout);
  freopen_s(&pCerr, LocalFolderFile("openssl.test.stderr.log").c_str(), "w", stderr);
  errorlevel=0;
  	{//call:ms\test.bat

		//set test="..\ms"
		//set opath="C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\CommonExtensions\Microsoft\TestWindow;C:\Program Files (x86)\Microsoft SDKs\F#\3.1\Framework\v4.0\;C:\Program Files (x86)\MSBuild\12.0\bin;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\BIN;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools;C:\WINDOWS\Microsoft.NET\Framework\v4.0.30319;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\VCPackages;C:\Program Files (x86)\HTML Help Workshop;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Team Tools\Performance Tools;C:\Program Files (x86)\Windows Kits\8.1\bin\x86;C:\Program Files (x86)\Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Loom\bin;C:\Program Files\TortoiseSVN\bin;C:\Program Files (x86)\GtkSharp\2.12\bin;C:\Program Files (x86)\Java\jdk1.7.0_25\bin;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files\OpenVPN\bin;C:\Program Files\doxygen\bin;C:\Program Files (x86)\nodejs\;C:\Program Files (x86)\sbt\;C:\Program Files\Perforce;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files (x86)\Microsoft SDKs\TypeScript\1.0\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files (x86)\Windows Live\Shared;C:\Strawberry\c\bin;C:\Strawberry\perl\site\bin;C:\Strawberry\perl\bin;C:\Users\David\.kre\packages\KRE-svrc50-x86.1.0.0-alpha3\bin;C:\Users\David\.kre\bin;k:\ruby193\bin;c:\jruby-1.7.4\bin;C:\Program Files (x86)\Java\jdk1.7.0_21\bin;K:\dev\mobile\apache-maven\bin;C:\Users\David\AppData\Roaming\npm;c:\python27;c:\python27\scripts;k:\dev\mobile\ZeroBraneStudio\bin;c:\Users\David\AppData\Local\atom\bin"
		//PATH="..\ms;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\CommonExtensions\Microsoft\TestWindow;C:\Program Files (x86)\Microsoft SDKs\F#\3.1\Framework\v4.0\;C:\Program Files (x86)\MSBuild\12.0\bin;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\BIN;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools;C:\WINDOWS\Microsoft.NET\Framework\v4.0.30319;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\VCPackages;C:\Program Files (x86)\HTML Help Workshop;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Team Tools\Performance Tools;C:\Program Files (x86)\Windows Kits\8.1\bin\x86;C:\Program Files (x86)\Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Loom\bin;C:\Program Files\TortoiseSVN\bin;C:\Program Files (x86)\GtkSharp\2.12\bin;C:\Program Files (x86)\Java\jdk1.7.0_25\bin;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files\OpenVPN\bin;C:\Program Files\doxygen\bin;C:\Program Files (x86)\nodejs\;C:\Program Files (x86)\sbt\;C:\Program Files\Perforce;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files (x86)\Microsoft SDKs\TypeScript\1.0\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files (x86)\Windows Live\Shared;C:\Strawberry\c\bin;C:\Strawberry\perl\site\bin;C:\Strawberry\perl\bin;C:\Users\David\.kre\packages\KRE-svrc50-x86.1.0.0-alpha3\bin;C:\Users\David\.kre\bin;k:\ruby193\bin;c:\jruby-1.7.4\bin;C:\Program Files (x86)\Java\jdk1.7.0_21\bin;K:\dev\mobile\apache-maven\bin;C:\Users\David\AppData\Roaming\npm;c:\python27;c:\python27\scripts;k:\dev\mobile\ZeroBraneStudio\bin;c:\Users\David\AppData\Local\atom\bin"
		//set OPENSSL_CONF="..\apps\openssl.cnf"

		//run this from inside the bin directory
		echo("rsa_test");
		{
			std::string argv[] = { "rsa_test" };
			dynload(L"rsa_test",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("destest");
		{
			std::string argv[] = { "destest" };
			dynload(L"destest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("ideatest");
		{
			std::string argv[] = { "ideatest" };
			dynload(L"ideatest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("bftest");
		{
			std::string argv[] = { "bftest" };
			dynload(L"bftest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("shatest");
		{
			std::string argv[] = { "shatest" };
			dynload(L"shatest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("sha1test");
		{
			std::string argv[] = { "sha1test" };
			dynload(L"sha1test",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("md5test");
		{
			std::string argv[] = { "md5test" };
			dynload(L"md5test",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("rc2test");
		{
			std::string argv[] = { "rc2test" };
			dynload(L"rc2test",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("rc4test");
		{
			std::string argv[] = { "rc4test" };
			dynload(L"rc4test",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("randtest");
		{
			std::string argv[] = { "randtest" };
			dynload(L"randtest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("dhtest");
		{
			std::string argv[] = { "dhtest" };
			dynload(L"dhtest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("exptest");
		{
			std::string argv[] = { "exptest" };
			dynload(L"exptest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("dsatest");
		{
			std::string argv[] = { "dsatest" };
			dynload(L"dsatest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("ectest");
		{
			std::string argv[] = { "ectest" };
			dynload(L"ectest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("testenc");
		{//call:..\ms\testenc openssl
			echo("start testenc");

			//path="..\ms;%path%"
			//set ssleay="openssl"
			//set input="..\ms\testenc.bat"
			//set tmp1="..\ms\cipher.out"
			//set out1="..\ms\clear.out"
			//set cmp="perl ..\ms\cmp.pl"

			{//call:tenc.bat enc
				//called by testenc
				echo("test enc");
				{
					std::string argv[] = { "openssl", "enc", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "enc", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_2;

				echo("test base64 enc");
				{
					std::string argv[] = { "openssl", "enc", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "enc", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_2:
				echo("err_2:");
			}//end:tenc.bat enc
			if(errorlevel) goto err_1;

			{//call:tenc.bat rc4
				//called by testenc
				echo("test rc4");
				{
					std::string argv[] = { "openssl", "rc4", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc4", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_3;

				echo("test base64 rc4");
				{
					std::string argv[] = { "openssl", "rc4", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc4", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_3:
				echo("err_3:");
			}//end:tenc.bat rc4
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-cfb
				//called by testenc
				echo("test des-cfb");
				{
					std::string argv[] = { "openssl", "des-cfb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-cfb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_4;

				echo("test base64 des-cfb");
				{
					std::string argv[] = { "openssl", "des-cfb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-cfb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_4:
				echo("err_4:");
			}//end:tenc.bat des-cfb
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede-cfb
				//called by testenc
				echo("test des-ede-cfb");
				{
					std::string argv[] = { "openssl", "des-ede-cfb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede-cfb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_5;

				echo("test base64 des-ede-cfb");
				{
					std::string argv[] = { "openssl", "des-ede-cfb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede-cfb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_5:
				echo("err_5:");
			}//end:tenc.bat des-ede-cfb
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede3-cfb
				//called by testenc
				echo("test des-ede3-cfb");
				{
					std::string argv[] = { "openssl", "des-ede3-cfb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3-cfb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_6;

				echo("test base64 des-ede3-cfb");
				{
					std::string argv[] = { "openssl", "des-ede3-cfb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3-cfb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_6:
				echo("err_6:");
			}//end:tenc.bat des-ede3-cfb
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ofb
				//called by testenc
				echo("test des-ofb");
				{
					std::string argv[] = { "openssl", "des-ofb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ofb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_7;

				echo("test base64 des-ofb");
				{
					std::string argv[] = { "openssl", "des-ofb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ofb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_7:
				echo("err_7:");
			}//end:tenc.bat des-ofb
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede-ofb
				//called by testenc
				echo("test des-ede-ofb");
				{
					std::string argv[] = { "openssl", "des-ede-ofb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede-ofb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_8;

				echo("test base64 des-ede-ofb");
				{
					std::string argv[] = { "openssl", "des-ede-ofb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede-ofb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_8:
				echo("err_8:");
			}//end:tenc.bat des-ede-ofb
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede3-ofb
				//called by testenc
				echo("test des-ede3-ofb");
				{
					std::string argv[] = { "openssl", "des-ede3-ofb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3-ofb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_9;

				echo("test base64 des-ede3-ofb");
				{
					std::string argv[] = { "openssl", "des-ede3-ofb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3-ofb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_9:
				echo("err_9:");
			}//end:tenc.bat des-ede3-ofb
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ecb
				//called by testenc
				echo("test des-ecb");
				{
					std::string argv[] = { "openssl", "des-ecb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ecb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_10;

				echo("test base64 des-ecb");
				{
					std::string argv[] = { "openssl", "des-ecb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ecb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_10:
				echo("err_10:");
			}//end:tenc.bat des-ecb
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede
				//called by testenc
				echo("test des-ede");
				{
					std::string argv[] = { "openssl", "des-ede", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_11;

				echo("test base64 des-ede");
				{
					std::string argv[] = { "openssl", "des-ede", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_11:
				echo("err_11:");
			}//end:tenc.bat des-ede
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede3
				//called by testenc
				echo("test des-ede3");
				{
					std::string argv[] = { "openssl", "des-ede3", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_12;

				echo("test base64 des-ede3");
				{
					std::string argv[] = { "openssl", "des-ede3", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_12:
				echo("err_12:");
			}//end:tenc.bat des-ede3
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-cbc
				//called by testenc
				echo("test des-cbc");
				{
					std::string argv[] = { "openssl", "des-cbc", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-cbc", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_13;

				echo("test base64 des-cbc");
				{
					std::string argv[] = { "openssl", "des-cbc", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-cbc", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_13:
				echo("err_13:");
			}//end:tenc.bat des-cbc
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede-cbc
				//called by testenc
				echo("test des-ede-cbc");
				{
					std::string argv[] = { "openssl", "des-ede-cbc", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede-cbc", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_14;

				echo("test base64 des-ede-cbc");
				{
					std::string argv[] = { "openssl", "des-ede-cbc", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede-cbc", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_14:
				echo("err_14:");
			}//end:tenc.bat des-ede-cbc
			if(errorlevel) goto err_1;

			{//call:tenc.bat des-ede3-cbc
				//called by testenc
				echo("test des-ede3-cbc");
				{
					std::string argv[] = { "openssl", "des-ede3-cbc", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3-cbc", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_15;

				echo("test base64 des-ede3-cbc");
				{
					std::string argv[] = { "openssl", "des-ede3-cbc", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "des-ede3-cbc", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_15:
				echo("err_15:");
			}//end:tenc.bat des-ede3-cbc
			if(errorlevel) goto err_1;

			{//call:tenc.bat idea-ecb
				//called by testenc
				echo("test idea-ecb");
				{
					std::string argv[] = { "openssl", "idea-ecb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-ecb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_16;

				echo("test base64 idea-ecb");
				{
					std::string argv[] = { "openssl", "idea-ecb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-ecb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_16:
				echo("err_16:");
			}//end:tenc.bat idea-ecb
			if(errorlevel) goto err_1;

			{//call:tenc.bat idea-cfb
				//called by testenc
				echo("test idea-cfb");
				{
					std::string argv[] = { "openssl", "idea-cfb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-cfb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_17;

				echo("test base64 idea-cfb");
				{
					std::string argv[] = { "openssl", "idea-cfb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-cfb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_17:
				echo("err_17:");
			}//end:tenc.bat idea-cfb
			if(errorlevel) goto err_1;

			{//call:tenc.bat idea-ofb
				//called by testenc
				echo("test idea-ofb");
				{
					std::string argv[] = { "openssl", "idea-ofb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-ofb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_18;

				echo("test base64 idea-ofb");
				{
					std::string argv[] = { "openssl", "idea-ofb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-ofb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_18:
				echo("err_18:");
			}//end:tenc.bat idea-ofb
			if(errorlevel) goto err_1;

			{//call:tenc.bat idea-cbc
				//called by testenc
				echo("test idea-cbc");
				{
					std::string argv[] = { "openssl", "idea-cbc", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-cbc", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_19;

				echo("test base64 idea-cbc");
				{
					std::string argv[] = { "openssl", "idea-cbc", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "idea-cbc", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_19:
				echo("err_19:");
			}//end:tenc.bat idea-cbc
			if(errorlevel) goto err_1;

			{//call:tenc.bat rc2-ecb
				//called by testenc
				echo("test rc2-ecb");
				{
					std::string argv[] = { "openssl", "rc2-ecb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-ecb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_20;

				echo("test base64 rc2-ecb");
				{
					std::string argv[] = { "openssl", "rc2-ecb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-ecb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_20:
				echo("err_20:");
			}//end:tenc.bat rc2-ecb
			if(errorlevel) goto err_1;

			{//call:tenc.bat rc2-cfb
				//called by testenc
				echo("test rc2-cfb");
				{
					std::string argv[] = { "openssl", "rc2-cfb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-cfb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_21;

				echo("test base64 rc2-cfb");
				{
					std::string argv[] = { "openssl", "rc2-cfb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-cfb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_21:
				echo("err_21:");
			}//end:tenc.bat rc2-cfb
			if(errorlevel) goto err_1;

			{//call:tenc.bat rc2-ofb
				//called by testenc
				echo("test rc2-ofb");
				{
					std::string argv[] = { "openssl", "rc2-ofb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-ofb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_22;

				echo("test base64 rc2-ofb");
				{
					std::string argv[] = { "openssl", "rc2-ofb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-ofb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_22:
				echo("err_22:");
			}//end:tenc.bat rc2-ofb
			if(errorlevel) goto err_1;

			{//call:tenc.bat rc2-cbc
				//called by testenc
				echo("test rc2-cbc");
				{
					std::string argv[] = { "openssl", "rc2-cbc", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-cbc", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_23;

				echo("test base64 rc2-cbc");
				{
					std::string argv[] = { "openssl", "rc2-cbc", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "rc2-cbc", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_23:
				echo("err_23:");
			}//end:tenc.bat rc2-cbc
			if(errorlevel) goto err_1;

			{//call:tenc.bat bf-ecb
				//called by testenc
				echo("test bf-ecb");
				{
					std::string argv[] = { "openssl", "bf-ecb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-ecb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_24;

				echo("test base64 bf-ecb");
				{
					std::string argv[] = { "openssl", "bf-ecb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-ecb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_24:
				echo("err_24:");
			}//end:tenc.bat bf-ecb
			if(errorlevel) goto err_1;

			{//call:tenc.bat bf-cfb
				//called by testenc
				echo("test bf-cfb");
				{
					std::string argv[] = { "openssl", "bf-cfb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-cfb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_25;

				echo("test base64 bf-cfb");
				{
					std::string argv[] = { "openssl", "bf-cfb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-cfb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_25:
				echo("err_25:");
			}//end:tenc.bat bf-cfb
			if(errorlevel) goto err_1;

			{//call:tenc.bat bf-ofb
				//called by testenc
				echo("test bf-ofb");
				{
					std::string argv[] = { "openssl", "bf-ofb", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-ofb", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_26;

				echo("test base64 bf-ofb");
				{
					std::string argv[] = { "openssl", "bf-ofb", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-ofb", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_26:
				echo("err_26:");
			}//end:tenc.bat bf-ofb
			if(errorlevel) goto err_1;

			{//call:tenc.bat bf-cbc
				//called by testenc
				echo("test bf-cbc");
				{
					std::string argv[] = { "openssl", "bf-cbc", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",11, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-cbc", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",11, argv, this);
				}
				if(errorlevel) goto err_27;

				echo("test base64 bf-cbc");
				{
					std::string argv[] = { "openssl", "bf-cbc", "-a", "-e", "-bufsize", "113", "-k", "test", "-in", "testenc.bat", "-out", LocalFolderFile("cipher.out") };
					dynload(L"openssl",12, argv, this);
				}
				{
					std::string argv[] = { "openssl", "bf-cbc", "-a", "-d", "-bufsize", "157", "-k", "test", "-in", LocalFolderFile("cipher.out"), "-out", LocalFolderFile("clear.out") };
					dynload(L"openssl",12, argv, this);
				}

				err_27:
				echo("err_27:");
			}//end:tenc.bat bf-cbc
			if(errorlevel) goto err_1;

			echo("OK");
			err_1:
			echo("err_1:");

		}//end:..\ms\testenc openssl
		if(errorlevel) goto done_0;

		echo("testpem");
		{//call:..\ms\testpem openssl
			//set ssleay="openssl"
			//set tmp1="pem.out"
			//set cmp="fc.exe"

			{//call:tpem.bat crl ..\test\testcrl.pem
				//called by testpem
				echo("test crl ..\test\testcrl.pem");
				{
					std::string argv[] = { "openssl", "crl", "-in", "testcrl.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat crl ..\test\testcrl.pem
			if(errorlevel) goto err_28;

			{//call:tpem.bat pkcs7 ..\test\testp7.pem
				//called by testpem
				echo("test pkcs7 ..\test\testp7.pem");
				{
					std::string argv[] = { "openssl", "pkcs7", "-in", "testp7.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat pkcs7 ..\test\testp7.pem
			if(errorlevel) goto err_28;

			{//call:tpem.bat req ..\test\testreq2.pem
				//called by testpem
				echo("test req ..\test\testreq2.pem");
				{
					std::string argv[] = { "openssl", "req", "-in", "testreq2.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat req ..\test\testreq2.pem
			if(errorlevel) goto err_28;

			{//call:tpem.bat rsa ..\test\testrsa.pem
				//called by testpem
				echo("test rsa ..\test\testrsa.pem");
				{
					std::string argv[] = { "openssl", "rsa", "-in", "testrsa.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat rsa ..\test\testrsa.pem
			if(errorlevel) goto err_28;

			{//call:tpem.bat x509 ..\test\testx509.pem
				//called by testpem
				echo("test x509 ..\test\testx509.pem");
				{
					std::string argv[] = { "openssl", "x509", "-in", "testx509.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat x509 ..\test\testx509.pem
			if(errorlevel) goto err_28;

			{//call:tpem.bat x509 ..\test\v3-cert1.pem
				//called by testpem
				echo("test x509 ..\test\v3-cert1.pem");
				{
					std::string argv[] = { "openssl", "x509", "-in", "v3-cert1.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat x509 ..\test\v3-cert1.pem
			if(errorlevel) goto err_28;

			{//call:tpem.bat x509 ..\test\v3-cert1.pem
				//called by testpem
				echo("test x509 ..\test\v3-cert1.pem");
				{
					std::string argv[] = { "openssl", "x509", "-in", "v3-cert1.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat x509 ..\test\v3-cert1.pem
			if(errorlevel) goto err_28;

			{//call:tpem.bat sess_id ..\test\testsid.pem
				//called by testpem
				echo("test sess_id ..\test\testsid.pem");
				{
					std::string argv[] = { "openssl", "sess_id", "-in", "testsid.pem", "-out", LocalFolderFile("pem.out") };
					dynload(L"openssl",6, argv, this);
				}

			}//end:tpem.bat sess_id ..\test\testsid.pem
			if(errorlevel) goto err_28;

			echo("OK");
			err_28:
			echo("err_28:");
		}//end:..\ms\testpem openssl
		if(errorlevel) goto done_0;

		echo("testss");
		{//call:..\ms\testss openssl

			//set ssleay=..\out\ssleay			//set ssleay="openssl"

			//set reqcmd="openssl req"
			//set x509cmd="openssl x509 -sha1"
			//set verifycmd="openssl verify"

			//set CAkey="keyCA.ss"
			//set CAcert="certCA.ss"
			//set CAserial="certCA.srl"
			//set CAreq="reqCA.ss"
			//set CAconf="..\test\CAss.cnf"
			//set CAreq2="req2CA.ss	"

			//set Uconf="..\test\Uss.cnf"
			//set Ukey="keyU.ss"
			//set Ureq="reqU.ss"
			//set Ucert="certU.ss"

			echo("make a certificate request using 'req'");
			{
				std::string argv[] = { "openssl", "req", "-config", "CAss.cnf", "-out", LocalFolderFile("reqCA.ss"), "-keyout", LocalFolderFile("keyCA.ss"), "-new" };
				dynload(L"openssl",9, argv, this);
			}
			if(errorlevel) goto e_req_37;

			echo("convert the certificate request into a self signed certificate using 'x509'");
			{
				std::string argv[] = { "openssl", "x509", "-sha1", "-CAcreateserial", "-in", LocalFolderFile("reqCA.ss"), "-days", "30", "-req", "-out", LocalFolderFile("certCA.ss"), "-signkey", LocalFolderFile("keyCA.ss"),  };
				dynload(L"openssl",13, argv, this);
			}
			if(errorlevel) goto e_x509_37;

			echo("--");
			echo("convert a certificate into a certificate request using 'x509'");
			{
				std::string argv[] = { "openssl", "x509", "-sha1", "-in", LocalFolderFile("certCA.ss"), "-x509toreq", "-signkey", LocalFolderFile("keyCA.ss"), "-out", LocalFolderFile("req2CA.ss"),  };
				dynload(L"openssl",10, argv, this);
			}
			if(errorlevel) goto e_x509_2_37;

			{
				std::string argv[] = { "openssl", "req", "-verify", "-in", LocalFolderFile("reqCA.ss"), "-noout" };
				dynload(L"openssl",6, argv, this);
			}
			if(errorlevel) goto e_vrfy_1_37;

			{
				std::string argv[] = { "openssl", "req", "-verify", "-in", LocalFolderFile("req2CA.ss"), "-noout" };
				dynload(L"openssl",6, argv, this);
			}
			if(errorlevel) goto e_vrfy_2_37;

			{
				std::string argv[] = { "openssl", "verify", "-CAfile", LocalFolderFile("certCA.ss"), LocalFolderFile("certCA.ss") };
				dynload(L"openssl",5, argv, this);
			}
			if(errorlevel) goto e_vrfy_3_37;

			echo("--");
			echo("make another certificate request using 'req'");
			{
				std::string argv[] = { "openssl", "req", "-config", "Uss.cnf", "-out", LocalFolderFile("reqU.ss"), "-keyout", LocalFolderFile("keyU.ss"), "-new",  };
				dynload(L"openssl",9, argv, this);
			}
			if(errorlevel) goto e_req_gen_37;

			echo("--");
			echo("sign certificate request with the just created CA via 'x509'");
			{
				std::string argv[] = { "openssl", "x509", "-sha1", "-CAcreateserial", "-in", LocalFolderFile("reqU.ss"), "-days", "30", "-req", "-out", LocalFolderFile("certU.ss"), "-CA", LocalFolderFile("certCA.ss"), "-CAkey", LocalFolderFile("keyCA.ss"), "-CAserial", LocalFolderFile("certCA.srl") };
				dynload(L"openssl",17, argv, this);
			}
			if(errorlevel) goto e_x_sign_37;

			{
				std::string argv[] = { "openssl", "verify", "-CAfile", LocalFolderFile("certCA.ss"), LocalFolderFile("certU.ss") };
				dynload(L"openssl",5, argv, this);
			}
			echo("--");
			echo("Certificate details");
			{
				std::string argv[] = { "openssl", "x509", "-sha1", "-subject", "-issuer", "-startdate", "-enddate", "-noout", "-in", LocalFolderFile("certU.ss") };
				dynload(L"openssl",10, argv, this);
			}

			echo("Everything appeared to work");
			echo("--");
			echo("The generated CA certificate is certCA.ss");
			echo("The generated CA private key is keyCA.ss");
			echo("The current CA signing serial number is in certCA.srl");

			echo("The generated user certificate is certU.ss");
			echo("The generated user private key is keyU.ss");
			echo("--");


			goto end_37;

			e_req_37:
			echo("e_req_37:");
			echo("error using 'req' to generate a certificate request");
			goto end_37;
			e_x509_37:
			echo("e_x509_37:");
			echo("error using 'x509' to self sign a certificate request");
			goto end_37;
			e_x509_2_37:
			echo("e_x509_2_37:");
			echo("error using 'x509' convert a certificate to a certificate request");
			goto end_37;
			e_vrfy_1_37:
			echo("e_vrfy_1_37:");
			echo("first generated request is invalid");
			goto end_37;
			e_vrfy_2_37:
			echo("e_vrfy_2_37:");
			echo("second generated request is invalid");
			goto end_37;
			e_vrfy_3_37:
			echo("e_vrfy_3_37:");
			echo("first generated cert is invalid");
			goto end_37;
			e_req_gen_37:
			echo("e_req_gen_37:");
			echo("error using 'req' to generate a certificate request");
			goto end_37;
			e_x_sign_37:
			echo("e_x_sign_37:");
			echo("error using 'x509' to sign a certificate request");
			goto end_37;

			end_37:
			echo("end_37:");
		}//end:..\ms\testss openssl
		if(errorlevel) goto done_0;

		//set SSL_TEST="ssltest -key keyU.ss -cert certU.ss -c_key keyU.ss -c_cert certU.ss -CAfile certCA.ss"

		echo("test sslv2");
		{
			std::string argv[] = { "ssltest", "-ssl2" };
			dynload(L"ssltest",2, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2 with server authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-ssl2", "-server_auth" };
			dynload(L"ssltest",13, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2 with client authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-ssl2", "-client_auth" };
			dynload(L"ssltest",13, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2 with both client and server authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-ssl2", "-server_auth", "-client_auth" };
			dynload(L"ssltest",14, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3");
		{
			std::string argv[] = { "ssltest", "-ssl3" };
			dynload(L"ssltest",2, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3 with server authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-ssl3", "-server_auth" };
			dynload(L"ssltest",13, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3 with client authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-ssl3", "-client_auth" };
			dynload(L"ssltest",13, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3 with both client and server authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-ssl3", "-server_auth", "-client_auth" };
			dynload(L"ssltest",14, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3");
		{
			std::string argv[] = { "ssltest" };
			dynload(L"ssltest",1, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 with server authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-server_auth" };
			dynload(L"ssltest",12, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 with client authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-client_auth" };
			dynload(L"ssltest",12, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 with both client and server authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-server_auth", "-client_auth" };
			dynload(L"ssltest",13, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2 via BIO pair");
		{
			std::string argv[] = { "ssltest", "-bio_pair", "-ssl2" };
			dynload(L"ssltest",3, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 with 1024 bit DHE via BIO pair");
		{
			std::string argv[] = { "ssltest", "-bio_pair", "-dhe1024dsa", "-v" };
			dynload(L"ssltest",4, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2 with server authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-ssl2", "-server_auth" };
			dynload(L"ssltest",14, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2 with client authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-ssl2", "-client_auth" };
			dynload(L"ssltest",14, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2 with both client and server authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-ssl2", "-server_auth", "-client_auth" };
			dynload(L"ssltest",15, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3 via BIO pair");
		{
			std::string argv[] = { "ssltest", "-bio_pair", "-ssl3" };
			dynload(L"ssltest",3, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3 with server authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-ssl3", "-server_auth" };
			dynload(L"ssltest",14, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3 with client authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-ssl3", "-client_auth" };
			dynload(L"ssltest",14, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv3 with both client and server authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-ssl3", "-server_auth", "-client_auth" };
			dynload(L"ssltest",15, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 via BIO pair");
		{
			std::string argv[] = { "ssltest", "-bio_pair" };
			dynload(L"ssltest",2, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 with server authentication");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-server_auth" };
			dynload(L"ssltest",13, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 with client authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-client_auth" };
			dynload(L"ssltest",13, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("test sslv2/sslv3 with both client and server authentication via BIO pair");
		{
			std::string argv[] = { "ssltest", "-key", LocalFolderFile("keyU.ss"), "-cert", LocalFolderFile("certU.ss"), "-c_key", LocalFolderFile("keyU.ss"), "-c_cert", LocalFolderFile("certU.ss"), "-CAfile", LocalFolderFile("certCA.ss"), "-bio_pair", "-server_auth", "-client_auth" };
			dynload(L"ssltest",14, argv, this);
		}
		if(errorlevel) goto done_0;

		echo("passed all tests");
		goto end_0;
		done_0:
		echo("done_0:");
		echo("problems.....");
		end_0:
		echo("end_0:");
		//PATH="C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\CommonExtensions\Microsoft\TestWindow;C:\Program Files (x86)\Microsoft SDKs\F#\3.1\Framework\v4.0\;C:\Program Files (x86)\MSBuild\12.0\bin;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\BIN;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\Tools;C:\WINDOWS\Microsoft.NET\Framework\v4.0.30319;C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\VCPackages;C:\Program Files (x86)\HTML Help Workshop;C:\Program Files (x86)\Microsoft Visual Studio 12.0\Team Tools\Performance Tools;C:\Program Files (x86)\Windows Kits\8.1\bin\x86;C:\Program Files (x86)\Microsoft SDKs\Windows\v8.1A\bin\NETFX 4.5.1 Tools\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Loom\bin;C:\Program Files\TortoiseSVN\bin;C:\Program Files (x86)\GtkSharp\2.12\bin;C:\Program Files (x86)\Java\jdk1.7.0_25\bin;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files\OpenVPN\bin;C:\Program Files\doxygen\bin;C:\Program Files (x86)\nodejs\;C:\Program Files (x86)\sbt\;C:\Program Files\Perforce;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;C:\Program Files (x86)\Microsoft SDKs\TypeScript\1.0\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files (x86)\Windows Live\Shared;C:\Strawberry\c\bin;C:\Strawberry\perl\site\bin;C:\Strawberry\perl\bin;C:\Users\David\.kre\packages\KRE-svrc50-x86.1.0.0-alpha3\bin;C:\Users\David\.kre\bin;k:\ruby193\bin;c:\jruby-1.7.4\bin;C:\Program Files (x86)\Java\jdk1.7.0_21\bin;K:\dev\mobile\apache-maven\bin;C:\Users\David\AppData\Roaming\npm;c:\python27;c:\python27\scripts;k:\dev\mobile\ZeroBraneStudio\bin;c:\Users\David\AppData\Local\atom\bin"
	}//end:ms\test.bat

  fclose(pCout);
  fclose(pCerr);
  {
    OutputDebugStringA("---------------STDOUT-------------\n");
    std::ifstream file(LocalFolderFile("openssl.test.stdout.log"));
    std::string temp;
    while (std::getline(file, temp))
    {
      OutputDebugStringA(temp.c_str());
      OutputDebugStringA("\r\n");
    }
  }
  {
    OutputDebugStringA("---------------STDERR-------------\n");
    std::ifstream file(LocalFolderFile("openssl.test.stderr.log"));
    std::string temp;
    while (std::getline(file, temp))
    {
      OutputDebugStringA(temp.c_str());
      OutputDebugStringA("\r\n");
    }
  }
  return errorlevel;
}