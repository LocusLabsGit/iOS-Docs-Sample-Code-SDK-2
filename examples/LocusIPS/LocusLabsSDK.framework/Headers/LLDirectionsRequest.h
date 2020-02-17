//
// Created by Rafal Hotlos on 2019-07-26.
// Copyright (c) 2019 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLPosition;


/**
 * The start and end points of a route, along with routing options.
 */
@interface LLDirectionsRequest : NSObject

/**
 * Constructor initiating with start and end position.
*/
- (nonnull instancetype)initWithStartPosition:(nonnull LLPosition *)startPosition endPosition:(nonnull LLPosition *)endPosition;

/**
 * The starting point for routing directions.
 */
@property (nonatomic, strong, nullable) LLPosition *startPosition;

/**
 * The end point for routing directions.
 */
@property (nonatomic, strong, nullable) LLPosition *endPosition;

@end


@interface LLDirectionsRequest (LLRoutingOptions)

/**
 * If set to <code>YES</code> it'll calculate route that is wheelchair accessible. If no wheelchair accessible route
 * exists it'll result in route not found.
 *
 * By default set to <code>NO</code>, meaning any route (wheelchair accessible or not) is accepted.
 */
@property (nonatomic) BOOL forceWheelchairAccessibleRoute;

/**
 * Set allowed security type ids for given security category id.
 *
 * See LLSecurity.h for available categories and types.
 *
 * @param securityTypeIds an array of [LLSecurityType typeId]
 * @param securityCategoryId [LLSecurityCategory categoryId]
 */
- (void)setSecurityTypeIds:(nullable NSArray<NSString *> *)securityTypeIds forSecurityCategoryId:(nonnull NSString *)securityCategoryId;

/**
 * Provides direct access to all configured security categories.
 *
 * Instead of setting this value directly, [LLDirectionsRequest setSecurityTypeIds:forSecurityCategoryId:] might be used
 * to configure the options by category.
 */
@property (nonatomic, strong, nullable) NSMutableDictionary<NSString *, NSArray<NSString *> *> *securityRoutingOptions;

@end

@interface LLDirectionsRequest (LLRoutingMultipleEndPositions)
/**
 * Initiates directions request with multiple end positions. This will create a route starting at startPosition and going
 * through all of the endPositions in the order as defined in the input array.
 *
 * If this constructor is used then [LLDirectionsRequest endPosition] will return the last endPosition and setting endPosition
 * will reset endPositions to just contain the one given end position.
 */
- (nonnull instancetype)initWithStartPosition:(nonnull LLPosition *)startPosition endPositions:(nonnull NSArray<LLPosition *> *)endPositions;

/**
 * Direct access to set endPositions, settings this property impacts the [LLDirectionsRequest endPosition].
 */
@property (nonatomic, strong, nullable) NSMutableArray<LLPosition *> *endPositions;
@end
