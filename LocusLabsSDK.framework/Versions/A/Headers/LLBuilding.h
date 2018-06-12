//
//  LLBuilding.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/12/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LLLocation.h"

@class LLBuilding;
@class LLFloor;

/**
 *  Delegate to process responses to the asynchonrous methods of a LLBuilding object.
 */
@protocol LLBuildingDelegate <NSObject>

@optional

/**
 *  The list of floors found in this building.
 *
 *  @param building the object which generated this list
 *  @param floors   an array of LLFloorInfo objects
 */
- (void)building:(LLBuilding *)building floorList:(NSArray *)floors;
- (void)building:(LLBuilding *)building floorLoaded:(LLFloor *)floor;

@end

@interface LLBuilding : LLLocation

@property (weak, nonatomic) id<LLBuildingDelegate> delegate;

/**
 * Contains the id of the default floor for this building
 */
@property (nonatomic,readonly) NSString *defaultFloorId;

/**
 *  Unique identifier for this building
 *
 *  @return the building identifier
 */
@property (nonatomic,readonly) NSString *buildingId;

/**
 *  Load and create a new instance of a LLFloor object for a specific floor of this building.
 *
 * **Deprecated return type:** In the future this method will have a <code>void</code> return type and will only provide the floor via the delegate <code>building:floorLoaded:</code> method
 *
 *  @param floorId the identifier of the floor to load
 */
- (LLFloor*)loadFloor:(NSString *)floorId;

/**
 *  Generate a list of the floors found in this building.
 *
 * **Deprecated return type:** In the future this method will have a <code>void</code> return type and will only provide the list of floors via the delegate <code>building:floorList:</code> method
 */
- (NSArray *)listFloors;

/**
 * getFloorIdForCLFloor
 */
- (NSString*)getFloorIdForCLFloor:(NSNumber*)clFloor;


/**
 * getFloorIdForOrdinal
 */
- (NSString*)getFloorIdForOrdinal:(NSNumber*)ordinal;

@end