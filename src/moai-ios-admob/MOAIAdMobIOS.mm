//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#import <moai-ios-admob/MOAIAdMobIOS.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	init
	@text	Initialize AdMob.
	
	
	@out 	nil
*/
int MOAIAdMobIOS::_init ( lua_State* L ) {
	
	MOAILuaState state ( L );
    
	NSLog(@"Google Mobile Ads SDK version: %@", [GADRequest sdkVersion]);
    
	return 0;
}

/**	@lua	useTestAds
	@text	Call this before any requests and it will use test ads
	
	
	@out 	nil
 */
int MOAIAdMobIOS::_useTestAds             ( lua_State* L ) {
    MOAILuaState state ( L );
    MOAIAdMobIOS::Get().isTest = true;
    return 0;
}

/**	@lua	loadBanner
	@text	Loads a banner in the background and shows it in the view
	
	
	@out 	nil
 */
int  MOAIAdMobIOS::_loadBanner            ( lua_State* L ) {
    MOAILuaState state ( L );
    MOAIAdMobIOS::Get().LoadBanner();
    return 0;
}

	
//================================================================//
// MOAIAdColonyIOS
//================================================================//

//----------------------------------------------------------------//
MOAIAdMobIOS::MOAIAdMobIOS () {
    isTest = false;
    _adview = NULL;
	RTTI_SINGLE ( MOAILuaObject )
}

//----------------------------------------------------------------//
MOAIAdMobIOS::~MOAIAdMobIOS () {
    
	
}

void MOAIAdMobIOS::LoadBanner() {
    GADRequest *r = [GADRequest request];
    
    //comment out this device for production
    if (isTest) {
      r.testDevices = @[ kGADSimulatorID ];
    }
    
    [_adview loadRequest:r];
}

void MOAIAdMobIOS::SetRootViewController (UIViewController *vc) {
    _viewController = vc;
}

void MOAIAdMobIOS::CreateAdView (UIViewController *vc) {
    NSLog(@"createAdView");
    UIView *view = vc.view;
    CGFloat width = 320;
    CGFloat height = 50;
    CGFloat marginleft = (view.frame.size.width - width)/2.0f;
    CGFloat margintop = (view.frame.size.height - height);
    NSLog(@"Size %f %f", marginleft, margintop);
    GADBannerView *bannerView = [[GADBannerView alloc ]initWithFrame: CGRectMake(marginleft, margintop, 320.0f, 50.0f)];
    _adview = bannerView;
    bannerView.adUnitID = @"ca-app-pub-3940256099942544/2934735716";
    [view addSubview:bannerView];
    bannerView.layer.zPosition = 10;
    
    bannerView.rootViewController = vc;
    
    
   }

//----------------------------------------------------------------//
void MOAIAdMobIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	
    
	luaL_Reg regTable [] = {
		{ "init",				_init },
        { "loadBanner",         _loadBanner },
        { "useTestAds",         _useTestAds },
		{ NULL, NULL }	
	};
    
	luaL_register( state, 0, regTable );
}

