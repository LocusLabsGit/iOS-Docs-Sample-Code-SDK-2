//
// Created by Rafal Hotlos on 06/03/2018.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLMap;
@class LLFloorView;


/**
 *  Base class for all objects which will be drawn on a map.
 *
 *  Set map to show the overlay. Set map to `nil` to remove it.
 *  It is recommended to set the map as the last step of the overlay configuration.
 */
@interface LLOverlay : NSObject

/**
 * The map this overlay is on.
 */
@property (nonatomic, weak) LLMap *map;

/**
 * Create overlay for given map.
 *
 * **Deprecated**: use init with no parameters and set map as the last step of overlay configuration"
 *
 * @param map the map this overlay is on
 *
 */
- (instancetype) initWithMap:(LLMap*)map __attribute__((deprecated("use init with no parameters and set map as the last step of overlay configuration")));

/**
 * The floor of the map which this object should be drawn on.  This floorView object is provided by a LLMapView. (**Deprecated**)
 *
 * **Deprecated**: replaced by setting map and floorId/position (depending on overlay type)
 */
@property (nonatomic, weak) LLFloorView *floorView __attribute__((deprecated("replaced by setting map and floorId/position (depending on overlay type)")));

/**
 *
 */
// TODO [api] not implemented on JS side
@property (nonatomic, strong) NSNumber *zIndex;


@end
