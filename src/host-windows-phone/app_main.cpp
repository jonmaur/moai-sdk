#include "pch.h"
#include "app.h"

using namespace Windows::ApplicationModel::Core;
using namespace Platform;

using namespace Moai;

// Implementation of the IFrameworkViewSource interface, necessary to run our app.
ref class MoaiApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView()
	{
		return ref new App();
	}
};

// The main function creates an IFrameworkViewSource for our app, and runs the app.
[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto moaiApplicationSource = ref new MoaiApplicationSource();
	CoreApplication::Run(moaiApplicationSource);
	return 0;
}