//
//  CursusMobileShoppingMain.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/5/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CursusSortFilterStoreVW.h"
#import "CursusStoreListVW.h"
//#import "CursusCustomerMenuVW.h"
#import "CursusActivityFullScreenVW.h"
//#import "CursusConfirmationVC.h"
#import "CursusAppTitleVW.h"
#import "CursusStoreSearchVW.h"
#import "CursusChooseAirportVC.h"
//#import "CursusSocialShareVC.h"
//#import "CursusOrderHistoryVC.h"
#import "AVFoundation/AVAudioPlayer.h"
#import "CursusBeaconContoller.h"
//#import "CursusGeoFence.h"
#import "CursusOrderHistoryV3.h"

@interface CursusMobileShoppingMain : NSObject

//@property (nonatomic, strong) CursusGeoFence *cursusGeoFence;
@property (nonatomic, strong) NSMutableDictionary *dictCursus;
@property (nonatomic, strong) NSMutableDictionary *dictCursusWatchKit;
@property (nonatomic, strong) NSMutableDictionary *dictOrder;
@property (nonatomic, strong) NSString *airportIdent;
@property (nonatomic, strong) NSNumber *airportVersion;
@property (nonatomic, strong) NSString *customerIdent;

@property (nonatomic, strong) CursusBeaconContoller *cursusBeaconContoller;
@property (nonatomic, strong) CursusAppTitleVW *vwAppTitle;
@property (nonatomic, strong) CursusActivityFullScreenVW *vwGreenLoader;
@property (nonatomic, strong) CursusSortFilterStoreVW *vwSortFilter;
//@property (nonatomic, strong) CursusConfirmationVC *vcConfirmation;
@property (nonatomic, strong) CursusStoreSearchVW *vwSearchStore;
//@property (nonatomic, strong) CursusCustomerMenuVW *vwMenuUser;
@property (nonatomic, strong) CursusChooseAirportVC *vcCursusAirport;
//@property (nonatomic, strong) CursusSocialShareVC *vcSocialShare;
@property (nonatomic, strong) CursusOrderHistoryV3 *vcOrderHistory;

@property (nonatomic, strong) NSMutableArray *arrStores;
@property (nonatomic, strong) NSMutableArray *arrFood;
@property (nonatomic, strong) NSMutableArray *arrRetail;
@property (nonatomic, strong) NSMutableArray *arrServices;

@property (nonatomic, strong) UIRefreshControl *grabRefreshControl;

@property (nonatomic, strong) AVAudioPlayer *audioPlayer;

@end
