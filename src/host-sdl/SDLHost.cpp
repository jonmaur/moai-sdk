// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <moai-core/host.h>
#include <host-modules/aku_modules.h>

#ifdef MOAI_OS_WINDOWS
    #include <windows.h>
#elif defined(MOAI_OS_LINUX)
    #include <X11/Xlib.h>      //XOpenDisplay,etc
    #include <xcb/xcb.h>
    #include <xcb/xcb_aux.h> 
    #include <xcb/randr.h>
#endif

#include <SDL.h>

#include "SDLHost.h"
#include "SDLJoystick.h"
#include "SDLKeyCodeMapping.h"

#include <host-sdl/MOAIDisplaySDL.h>

#include "imgui.h"
#include "imgui_impl_sdl_gl3.h"


#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#include <limits.h>
#endif

#define UNUSED(p) (( void )p)

namespace InputDeviceID {
	enum {
		DEVICE,
		PAD_0,
		PAD_1,
		PAD_2,
		PAD_3,
		TOTAL,
	};
}

namespace InputSensorID
{
	enum
	{
		KEYBOARD,
		POINTER,
		MOUSE_LEFT,
		MOUSE_MIDDLE,
		MOUSE_RIGHT,
		MOUSE_WHEEL,
		TOTAL,
	};
}

namespace GamepadSensorID
{
	enum
	{
		STICK_LEFT,
		STICK_RIGHT,
		TRIGGERS,
		BUTTONS,
		TOTAL
	};
}

namespace PadSensorButtonID
{
	enum
	{
		BUTTON_A,
		BUTTON_B,
		BUTTON_X,
		BUTTON_Y,
		BUTTON_START,
		BUTTON_BACK,

		BUTTON_LEFTSTICK,
		BUTTON_RIGHTSTICK,

		BUTTON_LEFTSHOULDER,
		BUTTON_RIGHTSHOULDER,

		BUTTON_DPAD_UP,
		BUTTON_DPAD_DOWN,
		BUTTON_DPAD_LEFT,
		BUTTON_DPAD_RIGHT,
		TOTAL
	};
}

static SDL_Window* sWindow = 0;

typedef int ( *DisplayModeFunc ) (int, SDL_DisplayMode *);

static void SetScreenSize ( DisplayModeFunc func);

//================================================================//
// aku callbacks
//================================================================//

void	_AKUEnterFullscreenModeFunc		();
void	_AKUExitFullscreenModeFunc		();
void	_AKUOpenWindowFunc				( const char* title, int width, int height );
void    _AKUShowCursor					();
void    _AKUHideCursor					();
void	_AKUSetTextInputRectFunc		( int xMin, int yMin, int xMax, int yMax );

//----------------------------------------------------------------//
void _AKUShowCursor () {
	SDL_ShowCursor(1);
}

//----------------------------------------------------------------//
void _AKUHideCursor () {
	SDL_ShowCursor(0);
}

//----------------------------------------------------------------//
void _AKUEnterFullscreenModeFunc () {

    //videomode change
    SDL_SetWindowFullscreen(sWindow, SDL_WINDOW_FULLSCREEN);
	SetScreenSize( SDL_GetCurrentDisplayMode );
}

//----------------------------------------------------------------//
void _AKUExitFullscreenModeFunc () {

    //videomode change
    SDL_SetWindowFullscreen(sWindow, 0);
	SetScreenSize( SDL_GetDesktopDisplayMode );
}

//----------------------------------------------------------------//
void _AKUOpenWindowFunc ( const char* title, int width, int height ) {
	
	if ( !sWindow ) {
		sWindow = SDL_CreateWindow ( title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
		SDL_GL_CreateContext ( sWindow );
		SDL_GL_SetSwapInterval ( 1 );
		AKUDetectGfxContext ();
		AKUSetViewSize ( width, height );
		AKUSdlSetWindow ( sWindow );

		// Enable keyboard text input.
		// According to the SDL documentation, this will open an on-screen keyboard on some platforms.
		// Currently we're using the SDL host for desktop platforms only, so this should not be a problem.
		SDL_StartTextInput ();
	}
	else {
		SDL_SetWindowSize ( sWindow, width, height );
	}

	MOAIDisplaySDL::SetWindowHandle(sWindow);
}

//----------------------------------------------------------------//
void _AKUSetTextInputRectFunc ( int xMin, int yMin, int xMax, int yMax ) {
	SDL_Rect sdlRect;
	sdlRect.x = xMin;
	sdlRect.y = yMin;
	sdlRect.w = xMax - xMin;
	sdlRect.h = yMax - yMin;
	
	SDL_SetTextInputRect ( &sdlRect );
}


//================================================================//
// helpers
//================================================================//

static void	Finalize			();
static void	Init				( int argc, char** argv );
static void	MainLoop			();
static void	PrintMoaiVersion	();
static void SetScreenDpi        ();

//----------------------------------------------------------------//
void Finalize () {

	AKUModulesAppFinalize ();
	AKUAppFinalize ();
	
	SDL_Quit ();
}

//----------------------------------------------------------------//
void Init ( int argc, char** argv ) {

	SDL_Init ( SDL_INIT_EVERYTHING );
	int nummappings = SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");
	printf("SDL Added %d mappings\n", nummappings);
	PrintMoaiVersion ();

	#ifdef _DEBUG
		printf ( "DEBUG BUILD\n" );
	#endif

	AKUAppInitialize ();
	AKUModulesAppInitialize ();

	AKUCreateContext ();
	AKUModulesContextInitialize ();
	AKUModulesRunLuaAPIWrapper ();

	AKUSetInputConfigurationName ( "SDL" );

	SetScreenSize( SDL_GetDesktopDisplayMode );

    SetScreenDpi();

	AKUReserveInputDevices			( InputDeviceID::TOTAL );
	AKUSetInputDevice				( InputDeviceID::DEVICE, "device" );
	
	AKUReserveInputDeviceSensors	( InputDeviceID::DEVICE, InputSensorID::TOTAL );
	AKUSetInputDeviceKeyboard		( InputDeviceID::DEVICE, InputSensorID::KEYBOARD,		"keyboard" );
	AKUSetInputDevicePointer		( InputDeviceID::DEVICE, InputSensorID::POINTER,		"pointer" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, InputSensorID::MOUSE_LEFT,		"mouseLeft" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, InputSensorID::MOUSE_MIDDLE,	"mouseMiddle" );
	AKUSetInputDeviceButton			( InputDeviceID::DEVICE, InputSensorID::MOUSE_RIGHT,	"mouseRight" );
	AKUSetInputDeviceWheel			( InputDeviceID::DEVICE, InputSensorID::MOUSE_WHEEL,	"mouseWheel" );
	//AKUSetInputDeviceJoystick       ( InputDeviceID::DEVICE, InputSensorID::JOYSTICK,	    "joystick" );

	// 4 gamepads
	char pad_name[16];
	for (int i = 0; i < 4; ++i)
	{
		sprintf(pad_name, "pad%d", i);

		AKUSetInputDevice(InputDeviceID::PAD_0 + i, pad_name);
		AKUSetInputDeviceActive(InputDeviceID::PAD_0 + i, false);
		AKUReserveInputDeviceSensors(InputDeviceID::PAD_0 + i, GamepadSensorID::TOTAL);
		AKUSetInputDeviceJoystick(InputDeviceID::PAD_0 + i, GamepadSensorID::STICK_LEFT, "stickLeft");
		AKUSetInputDeviceJoystick(InputDeviceID::PAD_0 + i, GamepadSensorID::STICK_RIGHT, "stickRight");
		AKUSetInputDeviceJoystick(InputDeviceID::PAD_0 + i, GamepadSensorID::TRIGGERS, "triggers");
		AKUSetInputDeviceKeyboard(InputDeviceID::PAD_0 + i, GamepadSensorID::BUTTONS, "buttons");
	}
	

	AKUSetFunc_EnterFullscreenMode ( _AKUEnterFullscreenModeFunc );
	AKUSetFunc_ExitFullscreenMode ( _AKUExitFullscreenModeFunc );

	AKUSetFunc_ShowCursor ( _AKUShowCursor );
	AKUSetFunc_HideCursor ( _AKUHideCursor );

	AKUSetFunc_OpenWindow ( _AKUOpenWindowFunc );
	
	AKUSetFunc_SetTextInputRect( _AKUSetTextInputRectFunc );

	REGISTER_LUA_CLASS(MOAIDisplaySDL)
	
	#ifdef __APPLE__
			//are we a bundle?
			CFBundleRef bref = CFBundleGetMainBundle();
			if (bref == NULL || CFBundleGetIdentifier(bref) == NULL) {
	AKUModulesParseArgs ( argc, argv );
	
			} else {
			
					CFURLRef bundleurl = CFBundleCopyResourcesDirectoryURL(bref);
					assert(bundleurl != NULL);
					
					UInt8 buf[PATH_MAX];
					CFURLGetFileSystemRepresentation(bundleurl, true, buf, PATH_MAX);

					AKUSetWorkingDirectory((const char *)buf);
					AKULoadFuncFromFile("bootstrap.lua");
					AKUCallFunc();
			}
	#else
			
			
		AKUModulesParseArgs ( argc, argv );
	#endif


	// Setup ImGui binding
	ImGui_ImplSdlGL3_Init(sWindow);

	
	atexit ( Finalize ); // do this *after* SDL_Init
}

// based on host-glut 
//void _onMultiButton( int touch_id, float x, float y, int state );
//void _onMultiButton( int touch_id, float x, float y, int state ) {
//
//	AKUEnqueueTouchEvent (
//		InputDeviceID::DEVICE,
//		InputSensorID::TOUCH,
//		touch_id,
//		state == SDL_FINGERDOWN,
//		( float )x,
//		( float )y
//	);
//}



//----------------------------------------------------------------//
void SetScreenSize(DisplayModeFunc func ) {

    SDL_DisplayMode dm;

    if ( func != NULL && func( 0, &dm ) == 0 ) {
    	AKUSetScreenSize(dm.w, dm.h);
    }
}


//----------------------------------------------------------------//
void SetScreenDpi() {

#ifdef MOAI_OS_WINDOWS

    HDC hDC = GetWindowDC(NULL);
    int widthInMm = GetDeviceCaps(hDC, HORZSIZE);
    double widthInInches = widthInMm / 25.4;
    int widthInPixels = GetDeviceCaps(hDC, HORZRES);
    AKUSetScreenDpi(( int )( widthInPixels / widthInInches ));

#elif defined(MOAI_OS_LINUX)

	char* display_name = getenv( "DISPLAY" );
	if ( !display_name ) return;

	int nscreen = 0;
	xcb_connection_t* conn = xcb_connect( display_name, &nscreen );
	if ( !conn ) return;

	xcb_screen_t* screen = xcb_aux_get_screen( conn, nscreen );

	double widthInInches = screen->width_in_millimeters / 25.4;
	int widthInPixels = screen->width_in_pixels;

	AKUSetScreenDpi(( int )widthInPixels / widthInInches );

	xcb_disconnect( conn );
  
#endif

}

//----------------------------------------------------------------//
void MainLoop () {

	printf("SDL num joysticks %d\n", SDL_NumJoysticks());
	Joystick* gamepads[] = {NULL, NULL, NULL, NULL};

	// create 4 gamepads and activate/deactivate them as needed
	gamepads[0] = new Joystick(0, InputDeviceID::PAD_0);
	gamepads[1] = new Joystick(1, InputDeviceID::PAD_1);
	gamepads[2] = new Joystick(2, InputDeviceID::PAD_2);
	gamepads[3] = new Joystick(3, InputDeviceID::PAD_3);

	//int num_devices_connected = SDL_NumJoysticks();

	for (int i = 0; i < 4; ++i)
	{
		gamepads[i]->Open();
	}
	
	SDL_GameControllerEventState(SDL_QUERY);
	
	Uint32 lastFrame = SDL_GetTicks();
	
	bool running = true;
	while ( running ) {
		
		SDL_Event sdlEvent;
		
		while ( SDL_PollEvent ( &sdlEvent )) {  
			
			ImGui_ImplSdlGL3_ProcessEvent(&sdlEvent);

			switch ( sdlEvent.type )  {
			
				case SDL_QUIT:
				
					running = false;
					break;
				
				case SDL_KEYDOWN:
				case SDL_KEYUP:	{
					if ( sdlEvent.key.repeat ) break;
					int moaiKeyCode = GetMoaiKeyCode ( sdlEvent );
					AKUEnqueueKeyboardKeyEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, moaiKeyCode, sdlEvent.key.type == SDL_KEYDOWN );
					break;
				}
				
				case SDL_TEXTINPUT: {
					AKUEnqueueKeyboardTextEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, sdlEvent.text.text );
					break;
				}
				case SDL_TEXTEDITING: {
					char *text = sdlEvent.edit.text;
					int start = sdlEvent.edit.start;
					int length = sdlEvent.edit.length;
					
					AKUEnqueueKeyboardEditEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, text, start, length, SDL_TEXTEDITINGEVENT_TEXT_SIZE );
					break;
				}
				
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
	
					switch ( sdlEvent.button.button ) {
					
						case SDL_BUTTON_LEFT:
							AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_LEFT, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
							break;
						
						case SDL_BUTTON_MIDDLE:
							AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_MIDDLE, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
							break;
						
						case SDL_BUTTON_RIGHT:
							AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_RIGHT, ( sdlEvent.type == SDL_MOUSEBUTTONDOWN ));
							break;
					}

					break;

				case SDL_MOUSEWHEEL: 

						if ( sdlEvent.wheel.which != SDL_TOUCH_MOUSEID ) {
                            //const int32_t x = sdlEvent.wheel.x;
							const int32_t y = sdlEvent.wheel.y; 

							//XXX: x or y ?
							AKUEnqueueWheelEvent ( InputDeviceID::DEVICE, InputSensorID::MOUSE_WHEEL, (float)y );
						}
					break;

					/*
					 * TODO:
					 * SDL_JOYBALLMOTION joystick trackball motion
					 * SDL_JOYHATMOTION	 joystick hat position change
					 * SDL_JOYBUTTONDOWN joystick button pressed
					 * SDL_JOYBUTTONUP	 joystick button released
					 * SDL_JOYDEVICEADDED	joystick connected
					 * SDL_JOYDEVICEREMOVED	joystick disconnected
					 * */
				case SDL_JOYAXISMOTION:
					{
						//float x, y;
						//int sensor = gamepads[sdlEvent.cdevice.which]->UpdateAxis(sdlEvent.jaxis.axis, &x, &y);
						//AKUEnqueueJoystickEvent(InputDeviceID::PAD_0 + sdlEvent.cdevice.which, sensor, x, y);
						// printf("SDL_JOYAXISMOTION %f, %f\n", x, y);
					}
					break;

				case SDL_CONTROLLERDEVICEADDED:
					printf("SDL_CONTROLLERDEVICEADDED\n");
					gamepads[sdlEvent.cdevice.which]->Open();
					AKUSetInputDeviceActive(InputDeviceID::PAD_0 + sdlEvent.cdevice.which, true);
					break;
				case SDL_JOYDEVICEREMOVED:
					printf("SDL_JOYDEVICEREMOVED\n");
					AKUSetInputDeviceActive(InputDeviceID::PAD_0 + sdlEvent.cdevice.which, false);
					gamepads[sdlEvent.cdevice.which]->Close();
					break;

				case SDL_MOUSEMOTION:
				
					AKUEnqueuePointerEvent ( InputDeviceID::DEVICE, InputSensorID::POINTER, sdlEvent.motion.x, sdlEvent.motion.y );
					break;

				case SDL_WINDOWEVENT:
					// Note: this only support fullscreen videomode change.
					// Not for the event "resize", by default SDL main window is not resizable(at least Linux)
					if ( sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED ||
							sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED ) {
						
						AKUSetViewSize(sdlEvent.window.data1, sdlEvent.window.data2);
					} else if ( sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_LOST ) {
						// If the focus is lost, it must be stopped.
						SDL_StopTextInput();
						
						// Clear Editing text.
						AKUEnqueueKeyboardEditEvent ( InputDeviceID::DEVICE, InputSensorID::KEYBOARD, "", 0, 0, SDL_TEXTEDITINGEVENT_TEXT_SIZE );
					} else if ( sdlEvent.window.event == SDL_WINDOWEVENT_FOCUS_GAINED ) {
						// Start when the focus is given.
						// TODO:Restored the edit text.
						SDL_StartTextInput();
					}
					break;

//                case SDL_FINGERDOWN:
//                case SDL_FINGERUP:
//                case SDL_FINGERMOTION:
//                    const int id    = ( int )sdlEvent.tfinger.fingerId;
//					const float x   = sdlEvent.tfinger.x;
//					const float y   = sdlEvent.tfinger.y;
//					const int state = ( sdlEvent.type == SDL_FINGERDOWN || sdlEvent.type == SDL_FINGERMOTION ) ? SDL_FINGERDOWN : SDL_FINGERUP;
//
//					_onMultiButton(id, x, y, state);
//
//					break;
			} //end_switch
		}//end_while

		for (int i = 0; i < 4; ++i)
		{
			float x, y;
			
			int sensor = gamepads[i]->UpdateAxis(SDL_CONTROLLER_AXIS_RIGHTX, &x, &y);
			AKUEnqueueJoystickEvent(InputDeviceID::PAD_0 + i, sensor, x, y);

			sensor = gamepads[i]->UpdateAxis(SDL_CONTROLLER_AXIS_LEFTX, &x, &y);
			AKUEnqueueJoystickEvent(InputDeviceID::PAD_0 + i, sensor, x, y);

			sensor = gamepads[i]->UpdateAxis(SDL_CONTROLLER_AXIS_TRIGGERLEFT, &x, &y);
			AKUEnqueueJoystickEvent(InputDeviceID::PAD_0 + i, sensor, x, y);

			bool buttonstate = false;
			for (int ii = 0; ii < SDL_CONTROLLER_BUTTON_MAX; ++ii)
			{
				if (gamepads[i]->UpdateButton(ii, &buttonstate))
				{
					// ii + 1 because lua arrays start at 1
					AKUEnqueueKeyboardKeyEvent(InputDeviceID::PAD_0 + i, GamepadSensorID::BUTTONS, ii + 1, buttonstate);
				}
			}
		}

		ImGui_ImplSdlGL3_NewFrame(sWindow);

		AKUModulesUpdate ();
		
		//bool show_test_window = true;
		//ImGui::ShowTestWindow(&show_test_window);

		AKURender ();

		ImGui::Render();

		SDL_GL_SwapWindow ( sWindow );
		
		Uint32 frameDelta = ( Uint32 )( AKUGetSimStep () * 1000.0 );
		Uint32 currentFrame = SDL_GetTicks ();
		Uint32 delta = currentFrame - lastFrame;
		
		if ( delta < frameDelta ) {
			SDL_Delay ( frameDelta - delta );
		}
		lastFrame = SDL_GetTicks();
	}

	for (int i = 0; i < 4; ++i)
	{
		gamepads[i]->Close();
	}
}

//----------------------------------------------------------------//
void PrintMoaiVersion () {

	static const int length = 255;
	char version [ length ];
	AKUGetMoaiVersion ( version, length );
	printf ( "%s\n", version );
}

//================================================================//
// SDLHost
//================================================================//

//----------------------------------------------------------------//
int SDLHost ( int argc, char** argv ) {

	Init ( argc, argv );

	if ( sWindow ) {
		MainLoop ();
	}

	return 0;
}
