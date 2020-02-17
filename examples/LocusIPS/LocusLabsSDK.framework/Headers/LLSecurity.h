//
// Created by Rafal Hotlos on 2019-07-01.
// Copyright (c) 2019 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/************************ Security categories ************************/
// Predefined security categories.
extern NSString *const _Nonnull LLSecurityCategorySecurityLane;
extern NSString *const _Nonnull LLSecurityCategoryImmigrationLane;

/************************ Security types ************************/
// Predefined types of "SecurityLane" security category
extern NSString *const _Nonnull LLSecurityLaneGeneral;
extern NSString *const _Nonnull LLSecurityLaneTSAPre;
extern NSString *const _Nonnull LLSecurityLaneClear;
extern NSString *const _Nonnull LLSecurityLanePriority;

// Predefined types of "ImmigrationLane" security category
extern NSString *const _Nonnull LLImmigrationLaneResident;
extern NSString *const _Nonnull LLImmigrationLaneVisitor;
extern NSString *const _Nonnull LLImmigrationLaneGlobalEntry;

@class LLSecurityType;

/**
 * A logical grouping of types of route security options, such as Security Lanes (for airport checkpoints), Immigration Lanes (for CBP checkpoints),
 * or Secured Employee Entrances (for smart campuses). A single venue can have multiple security categories.
 */
@interface LLSecurityCategory : NSObject

/**
 * Security categoryId to be used for configuring directions request and user preferences.
 *
 * There are constants for predefined category ids: <code>LLSecurityCategorySecurityLane</code>, <code>LLSecurityCategoryImmigrationLane</code>,
 * but this can be any category id supported by the venue.
 */
@property (nonatomic, readonly, nonnull) NSString *categoryId;
/**
 * An array of supported LLSecurityType
 */
@property (nonatomic, readonly, nonnull) NSArray<LLSecurityType *> *types;

@end

/**
 * A security category has one or more security types.
 * Example of security types are General and Clear for security lane category.
 */
@interface LLSecurityType : NSObject

/**
 * Security typeId to be used for configuring directions request and user preferences.
 *
 * There are constants for predefined type ids, for example <code>LLSecurityLaneGeneral</code> security lane or
 * <code>LLImmigrationLaneResident</code> immigration lane but this can be any type id supported by the venue.
 *
 * For the full list of predefined values see the LLSecurity header file.
 */
@property (nonatomic, readonly, nonnull) NSString *typeId;
/**
 * The name of security type to be used in user interface
 */
@property (nonatomic, readonly, nonnull) NSString *displayText;
/**
 * The (optional) name of logo file from LocusLabs resources
 */
@property (nonatomic, readonly, nullable) NSString *logo;
/**
 * Denotes if this is a default type for given category
 */
@property (nonatomic, readonly) BOOL isDefault;

@end
