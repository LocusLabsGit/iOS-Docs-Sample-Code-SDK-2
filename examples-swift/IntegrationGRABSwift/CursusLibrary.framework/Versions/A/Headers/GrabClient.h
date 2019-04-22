//
//  GrabClient.h
//  CursusLibrary
//
//  Created by Jarod Velasquez on 3/9/16.
//  Copyright © 2016 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GrabMenuInterface.h"
#import "GrabCheckoutInterface.h"
#import "GrabLoginInterface.h"
#import "GrabMapInterface.h"
#import "GrabClientInterface.h"

typedef void (^GrabClientDelegateRequestLoginHandler)(NSString *email, NSString *firstName, NSString *lastName, NSString *mobilePhone, NSString *mobilePhoneCountry, NSString *cartToken, NSString *userToken, NSError *error);

typedef void (^GrabCreateLoginPartnerCallback)(BOOL success, NSError *error);

@protocol GrabClientDelegate <NSObject>

@optional
-(void)grabOrderSuccessWithDetails:(NSDictionary *)details;
-(void)grabScreenLoaded:(NSDictionary *)details;
-(void)grabPartnerLoginRequestedFromViewController:(UIViewController *)fromViewController cartToken:(NSString *)cartToken handler:(GrabClientDelegateRequestLoginHandler)handler;
-(void)grabPartnerLoginCreated:(NSString *)email userToken:(NSString *)userToken handler:(GrabCreateLoginPartnerCallback)handler;
-(void)grabStartCancelledByUser;

@end

@interface GrabClient : NSObject<GrabClientInterface>

+(void)initializeGrabSDKwithCustomerCode:(NSString *)customerCode withCheckoutManager:(id<GrabCheckoutInterface>)checkoutManager andMenuManager:(id<GrabMenuInterface>)menuManager andLoginManager:(id<GrabLoginInterface>)loginManager andDictStyle:(NSMutableDictionary*)dictGrabStyle;
+(void)initializeGrabSDKwithCustomerCode:(NSString *)customerCode withCheckoutManager:(id<GrabCheckoutInterface>)checkoutManager andMenuManager:(id<GrabMenuInterface>)menuManager andLoginManager:(id<GrabLoginInterface>)loginManager andMapManager:(id<GrabMapInterface>)mapManager andDictStyle:(NSMutableDictionary*)dictGrabStyle;
+(id<GrabCheckoutInterface>)getCheckoutManager;
+(id<GrabMenuInterface>)getMenuManager;
+(id<GrabLoginInterface>)getLoginManager;
+(id<GrabMapInterface>)getMapManager;
+(id<GrabClientDelegate>)getGrabClientDelegate;
+(void)setGrabClientDelegate:(id<GrabClientDelegate>)delegate;
+(void)logGeoEventBeacon:(NSString*)iBeaconUUID major:(NSString*)major minor:(NSString*)minor whoFuncGrab:(NSString*)whoFuncGrab;
+(BOOL)deviceHasGrabOrderHistoryLocal;
+(NSString*)getGrabOrderHistoryLocalArray;
+(UIViewController *)getGrabOrderHistoryLocal;
+(BOOL)getPostCheckoutContinueHidden;
+(void)setPostCheckoutContinueHidden:(BOOL)postCheckoutContinueHidden;
+(BOOL)getPostCheckoutLeaveGrab;
+(void)setPostCheckoutLeaveGrab:(BOOL)postCheckoutLeaveGrab;
+(BOOL)clientInitializedSuccessfully;
+(void)updateGrabSettings;
+(void)setAlertTitle:(NSString *)title;
+(void)setDefaultFonts:(NSString*)fontDefault fontBold:(NSString*)fontBold fontItalic:(NSString*)fontItalic;
+(NSString *)getAlertTitle;
+(void)setAllowPartnerLogin:(BOOL)allowPartnerLogin;
+(BOOL)getAllowPartnerLogin;
+(void)logoutCustomer;
+(BOOL)isCustomerLoggedIn;
+(UIViewController *)getGrabCustomerOrderHistory;
+(void)setRootNavigationController:(UINavigationController *)rootNav;
+(UINavigationController *)getRootNavigationController;
+(void)setShowWhenToOrderConfirmationMessage:(BOOL)showWhenToOrder;
+(BOOL)shouldShowWhenToOrderConfirmationMessage;
+(BOOL)validatePhoneNumber:(NSString *)phoneNumber andCountry:(NSString *)country;
+(NSString *)getSSOLoginText;
+(void)setSSOLoginText:(NSString *)loginText;
+(void)setHideRetailServices:(BOOL)bHideRetailServices;
+(void)setShowTopFilterButtonOnHomeScreen:(BOOL)bShowTopFilterButtonOnHomeScreen;
+(BOOL)getHideRetailServices;
+(BOOL)getShowTopFilterButtonOnHomeScreen;
+(void)setFontMagnifier:(int)iFontMagnifier;
+(int)getSnackbarPeakHeightAdjustment;
+(void)setSnackbarPeakHeightAdjustment:(int)iPeakHeightAdjustment;
+(BOOL)getShowGrabLegalOnSplashView;
+(void)setShowGrabLegalOnSplashView:(BOOL)bShowGrabLegalOnSplashView;
+(UIColor *)colorWithHexString:(NSString *)hexString;
+(void)setPartnerTrackingToken:(NSString*)partnerTrackingToken;
+(NSString*)getPartnerTrackingToken;
+(void)setShowChangeAirportButton:(BOOL)bShowChangeAirportButton;
+(BOOL)getShowChangeAirportButton;
+(void)setLimitToOneInitialization:(BOOL)bLimitToOneInitialization;

@end
