//
//  LLPoint.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/9/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Describes a point in two dimentional space.
 */
@interface LLPoint : NSObject

/**
 *  Construct a new LLPoint with the given x and y values.
 *
 *  @param x the x value
 *  @param y the y value
 *
 *  @return the new point instance
 */
- (instancetype)initWithX:(NSNumber *)x Y:(NSNumber *)y;

/**
 *  The x value of this point.
 */
// TODO [api] changed to readonly in 2.0
@property (nonatomic, strong, readonly) NSNumber *x;

/**
 *  The y value of this point.
 */
// TODO [api] changed to readonly in 2.0
@property (nonatomic, strong, readonly) NSNumber *y;

/**
 *  Returns true if the two points are equal
 *
 *  @param other the point to compare against
 *
 *  @return true if the points are equal
 */
- (bool)equals:(LLPoint *)other;

@end