#include "host.h"
#include <stdio.h>
#include <moai-core/headers.h>
#include <moai-sim/MOAIEnvironment.h>
#include <string>

static std::string PlatformStringToCString(Platform::String ^platformString);

void AKUWinRTAppFinalize () {

}
void AKUWinRTAppInitialize () {

}
void AKUWinRTContextInitialize() {
	MOAIEnvironment &environment = MOAIEnvironment::Get ();

	//setup paths
	Platform::String ^resourcePathString = Windows::ApplicationModel::Package::Current->InstalledLocation->Path;
	const char *resourceDirectory = PlatformStringToCString(resourcePathString).c_str();
	environment.SetValue(MOAI_ENV_resourceDirectory, resourceDirectory);

	Platform::String ^documentDirectoryString = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	const char *documentDirectory = PlatformStringToCString(documentDirectoryString).c_str();
	environment.SetValue(MOAI_ENV_documentDirectory, documentDirectory);
}

static std::string PlatformStringToCString(Platform::String ^platformString) {
	std::wstring strW(platformString->Data());
	std::string strA(strW.begin(), strW.end());
	return strA;
}