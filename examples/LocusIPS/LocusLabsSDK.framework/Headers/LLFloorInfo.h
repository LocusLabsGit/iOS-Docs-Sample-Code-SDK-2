//
//  LLFloorInfo.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/12/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Provides the basic information about the floor of a building as returned by the LLBuilding listFloors method.
 */
@interface LLFloorInfo : NSObject

/**
 *  Uniquely identifies this floor.  This string is passed to the LLBuilding loadFloor: method to create an instance of an LLFloor object.
 */
@property (retain,nonatomic) NSString *floorId;

/**
 *  The localized name of this floor.
 */
@property (retain,nonatomic) NSString *name;

/**
 *  The localized details of this floor.
 */
@property (retain,nonatomic) NSString *details;

/**
 *  An integer which gives the relative position of this floor within the building. Also referred to as "ordinal"
 */
@property (retain,nonatomic) NSNumber *floor;

@end