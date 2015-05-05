#include "pch.h"
#include <stdio.h>
#include <string>

#include <moai-core/host.h>
#include <host-modules/aku_modules_winrt.h>


using namespace Moai;
using namespace Concurrency;
static void	PrintMoaiVersion();
static void moaiprintf(const char * format, ...);
static std::string PlatformStringToCString(Platform::String ^platformString);


critical_section akuLock;

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
	critical_section::scoped_lock lock(akuLock);
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
	critical_section::scoped_lock lock(akuLock);
	AKUDetectGfxContext();
}

void MoaiHost::Finalize() {
	critical_section::scoped_lock lock(akuLock);
	AKUModulesAppFinalize();
	AKUAppFinalize();
}

void MoaiHost::Render() {
	critical_section::scoped_lock lock(akuLock);
	AKURender();
}

void MoaiHost::Update() {
	critical_section::scoped_lock lock(akuLock);
	AKUModulesUpdate();
}

void MoaiHost::Pause(bool paused) {
	critical_section::scoped_lock lock(akuLock);
	AKUPause(paused);
}


void MoaiHost::PointerMove(int x, int y) {
	critical_section::scoped_lock lock(akuLock);
	AKUEnqueuePointerEvent(InputDeviceID::DEVICE, InputSensorID::POINTER, x, y);
}

void MoaiHost::PointerDown() {
	critical_section::scoped_lock lock(akuLock);
	AKUEnqueueButtonEvent(InputDeviceID::DEVICE, InputSensorID::TOUCH, true);
}

void MoaiHost::PointerUp() {
	critical_section::scoped_lock lock(akuLock);
	AKUEnqueueButtonEvent(InputDeviceID::DEVICE, InputSensorID::TOUCH, false);
}


void MoaiHost::OnSuspend() {
	critical_section::scoped_lock lock(akuLock);
	AKUModulesPause(true);
}
void MoaiHost::OnResume() {
	critical_section::scoped_lock lock(akuLock);
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