//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAIADMOBIOS_H
#define MOAIADMOBIOS_H

#include <moai-core/headers.h>

#import <GoogleMobileAds/GoogleMobileAds.h>

//================================================================//
// MOAIAdMobIOS
//================================================================//
class MOAIAdMobIOS :
public MOAIGlobalClass < MOAIAdMobIOS, MOAILuaObject >,
public MOAIGlobalEventSource {
private:
	GADBannerView *        _adview;
    UIViewController *     _viewController;
   
	//----------------------------------------------------------------//
	static int		_init					( lua_State* L );
    static int      _useTestAds             ( lua_State* L );
    static int      _loadBanner             ( lua_State* L );
public:

  DECL_LUA_SINGLETON ( MOAIAdMobIOS );
	 bool            isTest;

	//----------------------------------------------------------------//
					MOAIAdMobIOS					();
					~MOAIAdMobIOS				();
    void            CreateAdView                (UIViewController *vc);
    void            SetRootViewController       (UIViewController *vc);
    void            LoadBanner                    ();
	void			RegisterLuaClass				( MOAILuaState& state );
};

#endif // MOAIADMOBIOS_H