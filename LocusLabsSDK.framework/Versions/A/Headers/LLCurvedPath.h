//
//  LLCurvedPath.h
//  LocusLabsSDK
//
//  Created by Glenn Dierkes on 1/14/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLLatLng;

/**
 * The curved path.
 */
@interface LLCurvedPath : NSObject

/**
 *  **Deprecated**: this property is not used
 */
@property (nonatomic, strong) NSString* floorId __attribute__((deprecated("use position")));

@property (nonatomic, strong) NSArray<NSArray<LLLatLng *> *>* curves;

/**
 * Add the given curve object to the end of the path.
 * A curve is an NSArray of 4 LLLatLngs. It's interpreted as @[P0, P1, P2, P3] - four control pints of a Bezier curve.
 *
 * @param curve the curve to add
 */
//TODO [api] add migration guide that describes the mapping from "start", "out", "in", "end" to P0-P3 (in this order)
// note that for JS it's start/in/out/end... so the control points are switched
- (void)addCurve:(NSArray<LLLatLng *> *)curve;

@end