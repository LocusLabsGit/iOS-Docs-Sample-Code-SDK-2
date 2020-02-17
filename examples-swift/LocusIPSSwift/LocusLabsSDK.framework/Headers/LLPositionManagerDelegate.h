//
//  LLPositionManagerDelegate.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/16/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLPositionManager;
@class LLPosition;
@class LLBeacon;

/**
 *  This protocol should be implemented by any object which will be used as a delegate for a LLPositionManager object.
 */
@protocol LLPositionManagerDelegate <NSObject>

@optional

/**
 *  This method is called by LLPositionManager whenever the device's position has changed.
 *
 *  @param positionManager the position manager which generated the position
 *  @param position        the new position
 */
- (void)positionManager:(LLPositionManager *)positionManager positionChanged:(LLPosition *)position;

/**
 *  This method is called if positioning functionality either becomes available or is no longer available.
 *
 *  @param positionManager      the position manager
 *  @param positioningAvailable whether or not positioning is available
 */
- (void)positionManager:(LLPositionManager *)positionManager positioningAvailable:(BOOL)positioningAvailable;

@end