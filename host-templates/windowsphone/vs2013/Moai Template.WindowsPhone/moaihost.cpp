#include "pch.h"
#include <stdio.h>
#include <moai-core/host.h>
#include <zl-vfs/headers.h>
#include <host-modules/aku_modules.h>
#include "moaihost.h"

using namespace Moai;

static void	PrintMoaiVersion();
static void moaiprintf(const char * format, ...);


MoaiHost::MoaiHost() {

}

MoaiHost::~MoaiHost() {
}

void MoaiHost::Init(int width,int height, int dpi) {
	PrintMoaiVersion();
	AKUAppInitialize();
	AKUModulesAppInitialize();

	AKUCreateContext();
	AKUModulesContextInitialize();
	AKUModulesRunLuaAPIWrapper();

	AKUDetectGfxContext();
	AKUSetViewSize(width, height);
	AKUSetScreenDpi(dpi);
	AKUSetScreenSize(width, height);

	

	zl_printf("testing 1 2 3");

	AKULoadFuncFromFile("bootstrap.lua");
	AKUCallFunc();
	zl_printf("testing 1 2 3\n\n");

}

void MoaiHost::RedetectGraphicsContext() {
	AKUDetectGfxContext();
}

void MoaiHost::Finalize() {
	AKUModulesAppFinalize();
	AKUAppFinalize();
}

void MoaiHost::Render() {
	AKURender();
}

void MoaiHost::Update() {
	AKUModulesUpdate();
}

void MoaiHost::Pause(bool paused) {
	AKUPause(paused);
}

void PrintMoaiVersion() {
	static const int length = 255;
	char version[length];
	AKUGetMoaiVersion(version, length);
	OutputDebugString(L"About to print version:");
	moaiprintf("%s\n", version);
}

void moaiprintf(const char * format, ...) {
	char buffer[1024];
	va_list args;
	va_start(args, format);
	_vsnprintf_s(buffer, 1023, format, args);
	OutputDebugStringA(buffer);
}