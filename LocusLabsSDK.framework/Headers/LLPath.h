//
//  LLPath.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/26/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLCurvedPath.h"

@class LLLatLng;

/**
 * The path of points used to describe a polyline.
 */
@interface LLPath : NSObject

- (NSArray*)points;

/**
 *
 *  Add the given LLLatLng to the end of the path
 *
 *  @param latLng the LLLatLng to add
 */
- (void)addLatLng:(LLLatLng *)latLng;


@end