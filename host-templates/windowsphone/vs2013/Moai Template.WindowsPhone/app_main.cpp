#include "pch.h"
#include "app.h"

using namespace Windows::ApplicationModel::Core;
using namespace Platform;

using namespace Moai;

// Implementation of the IFrameworkViewSource interface, necessary to run our app.
ref class HelloTriangleApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
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
	auto helloTriangleApplicationSource = ref new HelloTriangleApplicationSource();
	CoreApplication::Run(helloTriangleApplicationSource);
	return 0;
}