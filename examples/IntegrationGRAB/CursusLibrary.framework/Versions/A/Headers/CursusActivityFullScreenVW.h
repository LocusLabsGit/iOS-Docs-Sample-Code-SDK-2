//
//  CursusActivityFullScreenVW.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/5/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CursusSpinnerView.h"

@class CursusActivityFullScreenVW;

@protocol CursusActivityFullScreenVWDelegate <NSObject>

@optional
- (void) cursusActivityFullScreenVWCancellRequested: (CursusActivityFullScreenVW *) screen;

@end

@interface CursusActivityFullScreenVW : UIView

@property (nonatomic, strong) NSString *city;
@property (nonatomic, strong) NSString *airportIdent;
@property (nonatomic, strong) UILabel *lblMessage1;
@property (nonatomic, strong) UILabel *lblMessage2;
@property (nonatomic, strong) UILabel *lblGrab;
@property (nonatomic, strong) UIView *vwGrab;
@property (nonatomic, strong) UIImageView *imgGrab;
@property (nonatomic, strong) UIActivityIndicatorView *loadingCursusData;
@property (nonatomic, strong) CursusSpinnerView *vwSpinner;
@property (nonatomic, strong) UIImageView *vwBackground;
@property (nonatomic, strong) UIButton *cancelButton;
@property (nonatomic) BOOL bUpdatingLoader;

@property id<CursusActivityFullScreenVWDelegate> delegate;
@property (nonatomic) BOOL bWithinGeoFence;

-(void)updateGreenLoaderWithComplete:(void (^)(void))complete;
-(void)resizeToFit;
-(void)setCancelEnabled:(BOOL)cancelAllowed;
-(void)updateGreenLoaderWithAirportIdent:(NSString *)airportIdent andCity:(NSString *)city;
-(void)setAttributedStringMessage2:(NSAttributedString*)attrMessage2;
@end
