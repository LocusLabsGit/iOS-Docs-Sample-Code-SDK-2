//
//  CursusMobileShoppingVC.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/4/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CursusMobileShoppingMain.h"
#import "CursusBaseViewController.h"
@class CursusNotificationBar;

@interface CursusMobileShoppingVC : CursusBaseViewController <UIGestureRecognizerDelegate>
{
    CursusMobileShoppingMain *cursusMobileShoppingMain;
}

@property (nonatomic, strong) CursusMobileShoppingMain *cursusMobileShoppingMain;

@property (weak, nonatomic) IBOutlet NSLayoutConstraint *vwMainHomeLeftConstraint;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *vwMainHomeRightConstraint;

@property (weak, nonatomic) IBOutlet NSLayoutConstraint *topContainerTopConstraint;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint *topContainerHeightConstraint;

@property (nonatomic, strong) IBOutlet UIView *vwMainHome;
@property (nonatomic, strong) IBOutlet UIView *vwMapFilterBottom;
@property (nonatomic, strong) IBOutlet UIView *vwTopContainer;

@property (nonatomic, strong) IBOutlet UIView *imgMainFood;
@property (nonatomic, strong) IBOutlet UIView *imgMainRetail;
@property (nonatomic, strong) IBOutlet UIView *imgMainServices;

@property (nonatomic, strong) IBOutlet UIButton *btnMainFood;
@property (nonatomic, strong) IBOutlet UIButton *btnMainRetail;
@property (nonatomic, strong) IBOutlet UIButton *btnMainServices;
@property (nonatomic, strong) IBOutlet UIButton *btnCategory;
@property (nonatomic, strong) IBOutlet UIButton *btnMapShopping;

@property (nonatomic, strong) IBOutlet CursusStoreListVW *tvShopping;

@property (nonatomic, strong) UILabel *lblGuestCheckoutLine;
@property (nonatomic, strong) UIButton *btnSearchStore;
@property (nonatomic, strong) UIButton *btnUserMenu;
@property (nonatomic) CursusNotificationBar *notificationBar;

-(id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil customerCode:(NSString*)customerCode airportCode:(NSString*)airportCode showTitle:(BOOL)showTitle terminalName:(NSString *)terminalName;

-(id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil customerCode:(NSString*)customerCode airportCode:(NSString*)airportCode showTitle:(BOOL)showTitle poiID:(NSString *)poiID;
-(id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil customerCode:(NSString*)customerCode airportCode:(NSString*)airportCode showTitle:(BOOL)showTitle pointrPOIID:(NSString *)pointrPOIID;
-(id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil customerCode:(NSString*)customerCode airportCode:(NSString*)airportCode showTitle:(BOOL)showTitle waypointID:(NSString *)waypointID;
-(NSDictionary*)getCursusWatchKit;
-(BOOL)checkForRatingOrTippingFromPushNotification;
-(void)checkForMapNavigation;
-(void)showHelpVC;
-(void)showSocialShareVC;
-(void)showStoreRatings:(NSMutableDictionary*)dictOrder;
-(void)btnHoldOrder_CancelOrderTouchUpInside:(NSMutableDictionary*)dictOrderDetail;
-(void)hideSnackbar;

@end
