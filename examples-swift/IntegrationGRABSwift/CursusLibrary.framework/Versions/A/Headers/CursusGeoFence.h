//
//  CursusGeoFence.h
//  CursusLibrary
//
//  Created by Michael Natale on 8/31/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "CursusGeo.h"

@protocol CursusGeoFenceRegionEnteredDelegate <NSObject>

-(void)enteredRegionWithIdentifier:(NSString *)identifier;

@end

@interface CursusGeoFence : NSObject
{
//    NSMutableArray *arrOrderHistory;
//    NSTimer *tmrAirportSearch;
//    CursusGeo *geo;
}

//@property (nonatomic, strong) NSMutableArray *arrOrderHistory;
//@property (nonatomic, strong) NSTimer *tmrAirportSearch;
//@property (nonatomic, strong) CursusGeo *geo;

@property (weak, nonatomic) id<CursusGeoFenceRegionEnteredDelegate> delegate;

+ (CursusGeoFence *)sharedInstance;
+ (CLCircularRegion *)createRegionFromLatitude:(double)latitude longitude:(double)longitude radius:(double)radius andRegionIdentifier:(NSString *)regionIdentifier;
- (void)registerRegionArray:(NSArray *)regionArray;
- (void)unregiesterRegionWithIdentifier:(NSString *)identifier;
- (void)registerCircularRegion:(CLCircularRegion *)region;
+ (NSString *)addPrefixToRegionIdentifier:(NSString *)regionIdentifier;
+ (NSString *)removePrefixFromRegionIdentifier:(NSString *)regionIdentifier;

@end
