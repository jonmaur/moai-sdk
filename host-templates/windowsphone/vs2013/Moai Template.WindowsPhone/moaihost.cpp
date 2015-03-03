#include "pch.h"
#include <stdio.h>
#include <string>

#include <moai-core/host.h>
#include <host-modules/aku_modules_winrt.h>

#include "moaihost.h"

using namespace Moai;

static void	PrintMoaiVersion();
static void moaiprintf(const char * format, ...);
static std::string PlatformStringToCString(Platform::String ^platformString);

namespace InputDeviceID {
	enum {
		DEVICE,
		TOTAL,
	};
}

namespace InputSensorID {
	enum {
		KEYBOARD,
		POINTER,
		TOUCH,
		TOTAL,
	};
}

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

	AKUSetInputConfigurationName("WinRT");

	AKUReserveInputDevices(InputDeviceID::TOTAL);
	AKUSetInputDevice(InputDeviceID::DEVICE, "device");

	AKUReserveInputDeviceSensors(InputDeviceID::DEVICE, InputSensorID::TOTAL);
	AKUSetInputDeviceKeyboard(InputDeviceID::DEVICE, InputSensorID::KEYBOARD, "keyboard");
	AKUSetInputDevicePointer(InputDeviceID::DEVICE, InputSensorID::POINTER, "pointer");
	AKUSetInputDeviceButton(InputDeviceID::DEVICE, InputSensorID::TOUCH, "touch");


	AKUDetectGfxContext();
	AKUSetViewSize(width, height);
	AKUSetScreenDpi(dpi);
	AKUSetScreenSize(width, height);

	Platform::String ^resourcePathString = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
	std::string resourceDir = PlatformStringToCString(resourcePathString);
	AKUSetWorkingDirectory(resourceDir.c_str());

	AKULoadFuncFromFile("init.lua");
	AKUCallFunc();

	AKULoadFuncFromFile("bootstrap.lua");
	AKUCallFunc();

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


void MoaiHost::PointerMove(int x, int y) {
	AKUEnqueuePointerEvent(InputDeviceID::DEVICE, InputSensorID::POINTER, x, y);
}

void MoaiHost::PointerDown() {
	AKUEnqueueButtonEvent(InputDeviceID::DEVICE, InputSensorID::TOUCH, true);
}

void MoaiHost::PointerUp() {
	AKUEnqueueButtonEvent(InputDeviceID::DEVICE, InputSensorID::TOUCH, false);
}


void MoaiHost::OnSuspend() {
	AKUModulesPause(true);
}
void MoaiHost::OnResume() {
	AKUModulesPause(false);
}



static std::string PlatformStringToCString(Platform::String ^platformString) {
	std::wstring strW(platformString->Data());
	std::string strA(strW.begin(), strW.end());
	return strA;
}


void PrintMoaiVersion() {
	static const int length = 255;
	char version[length];
	AKUGetMoaiVersion(version, length);
	moaiprintf("%s\n", version);
}

void moaiprintf(const char * format, ...) {
	va_list args;
	va_start(args, format);
	char buffer[1024];
	_vsnprintf_s(buffer, 1024, format, args);



	size_t newsize = strlen(buffer) + 1;
	wchar_t * wbuffer = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wbuffer, newsize, buffer, _TRUNCATE);
	

	OutputDebugString(wbuffer);
	delete[] wbuffer;
	
}