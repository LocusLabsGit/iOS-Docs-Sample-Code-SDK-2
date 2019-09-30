//
// Created by Rafal Hotlos on 05/12/2018.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * This class is used for configuring user preferences.
 * It has a singleton instance which is accessed via the [LLUserPreferences shared] method.
 */
@interface LLUserPreferences : NSObject

/**
 * Shared user preferences object.
 */
+ (nonnull instancetype)shared NS_SWIFT_NAME(shared());

/**
 * Prefer the wheelchair accessible routes when navigating. NO by default.
 */
@property (nonatomic) BOOL preferWheelchairAccessibleNavigation;

/**
 * Set user preferences for security category (lanes).
 *
 * For example: <code>[preferences setSecurityTypeIds:@[LLSecurityLaneGeneral, LLSecurityLaneTSAPre] forSecurityCategoryId:LLSecurityCategorySecurityLane]</code>
 *
 * See LLSecurity.h for available categories and types.
 *
 * @param securityTypeIds an array of [LLSecurityType typeId]
 * @param securityCategoryId [LLSecurityCategory categoryId]
 */
- (void)setSecurityTypeIds:(nullable NSArray<NSString *> *)securityTypeIds forSecurityCategoryId:(nonnull NSString *)securityCategoryId;

/**
 * Returns an array of security types for given security category id. This might be <code>nil</code> if no preferences were set for given category id.
 * @param securityCategoryId [LLSecurityCategory categoryId]
 * @return an array of [LLSecurityType typeId]
 */
- (nullable NSArray<NSString *>*)getSecurityTypeIdsForSecurityCategoryId:(nonnull NSString *)securityCategoryId;

@end
