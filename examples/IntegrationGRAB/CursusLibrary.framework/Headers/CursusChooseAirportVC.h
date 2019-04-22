//
//  CursusChooseAirportVW.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/5/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CursusAirport.h"
#import "CursusGeo.h"
#import "CursusBaseViewController.h"

@protocol CursusChooseAirportDelegate <NSObject>

-(void)airportSelected:(NSDictionary *)dictAirport;

@end

@interface CursusChooseAirportVC : CursusBaseViewController <UITableViewDataSource, UITableViewDelegate>
{
    CursusAirport *airports;
    NSArray *arrAirports;
    NSMutableArray *arrRecents;
    UITableView *tvAirports;
    UITableView *tvRecents;
    UITextField *txtAirportSearch;
    UIButton *btnCancel;
    UIButton *btnClearRecents;
    UIButton *btnClose;
    UILabel *lblAirportTitle;
    UILabel *lblRecentsTitle;
    UILabel *lblCurrentAirportLeft;
    UILabel *lblCurrentAirportRight;
    UILabel *lblCurrentLocation;
    UILabel *lblAvailableAirports;
    UIImageView *imgGlassIcon;
    UIButton *btnChooseCurrentLocationAirport;
    UIButton *btnGPSNearestAirport;
    UIView *vwTopBackground;
    UIView *circleGreenCurrentLocation;
    NSString *currentAirportIdent;
    CursusAirport *cursusAirport;
    CursusGeo *geo;
}

@property (nonatomic, strong) CursusGeo *geo;
@property (nonatomic, strong) CursusAirport *airports;
@property (nonatomic, strong) NSArray *arrAirports;
@property (nonatomic, strong) NSMutableArray *arrRecents;
@property (nonatomic, strong) UITableView *tvAirports;
@property (nonatomic, strong) UITableView *tvRecents;
@property (nonatomic, strong) UITextField *txtAirportSearch;
@property (nonatomic, strong) UIButton *btnClose;
@property (nonatomic, strong) UIButton *btnCancel;
@property (nonatomic, strong) UIButton *btnClearRecents;
@property (nonatomic, strong) UIButton *btnChooseCurrentLocationAirport;
@property (nonatomic, strong) UIButton *btnGPSNearestAirport;
@property (nonatomic, strong) UILabel *lblAirportTitle;
@property (nonatomic, strong) UILabel *lblCurrentLocation;
@property (nonatomic, strong) UILabel *lblAvailableAirports;
@property (nonatomic, strong) UILabel *lblCurrentAirportLeft;
@property (nonatomic, strong) UILabel *lblCurrentAirportRight;
@property (nonatomic, strong) UILabel *lblRecentsTitle;
@property (nonatomic, strong) UIImageView *imgGlassIcon;
@property (nonatomic, strong) UIView *vwTopBackground;
@property (nonatomic, strong) UIView *circleGreenCurrentLocation;
@property (nonatomic, strong) NSString *currentAirportIdent;
@property (nonatomic, strong) CursusAirport *cursusAirport;
@property (nonatomic, weak) id<CursusChooseAirportDelegate> delegate;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil  bCursusOnly:(BOOL)bCursusOnly bCursusOnlyWithActiveStoreMenus:(BOOL)bCursusOnlyWithActiveStoreMenus;
//-(void)addtarget:(id)target action:(SEL)method;
-(void)reloadAirports;
-(void)resizeToFit;

@end
