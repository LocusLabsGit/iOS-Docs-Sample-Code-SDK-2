//
// Created by Rafal Hotlos on 2019-01-30.
// Copyright (c) 2019 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/************************ Attributes ************************/
typedef NSString * LLMapViewPreferencesKey NS_EXTENSIBLE_STRING_ENUM;
// Predefined attributes for preferences. If the key is not present in the dictionary, it indicates the default value described below.

// This parameter controls if point POIs should be hidden if current map radius is greater than given value.
// By default it's set to @55 to enable hiding of point POIs.
// Can be set to nil, meaning the point POIs are always visible.
extern LLMapViewPreferencesKey const _Nonnull LLMapViewPreferencesKeyPointPOIsHideForRadiusGreaterThan; // NSNumber, default 55

// This parameter controls whether point POIs should be scaled when the map radius changes.
// It can be configured with an NSDictionary with given structure:
// @{
//   @"fromRadius": @40, @"fromScale": @1,
//   @"toRadius": @15, @"toScale": @0.6,
// }
// This means that for map radius >= 40 the scale should be 1, between 40 and 15 the scale should be scaled linearly
// from 1 to 0.6 and below map radius 15, the scale should be 0.6
// The above mentioned values are the defaults for this setting.
// It can be set to nil, meaning the point POIs have always the scale = 1.
extern LLMapViewPreferencesKey const _Nonnull LLMapViewPreferencesKeyPointPOIsResize; // NSDictionary


@interface LLMapViewPreferences : NSObject

+ (nonnull instancetype)shared NS_SWIFT_NAME(shared());

/**
 * stores a value (or removes the value if nil is passed as the value) for the provided key in the preferences
 */
- (void)setObject:(nullable id)value forKey:(nonnull LLMapViewPreferencesKey)key;
/**
 * provides a subscript access to store a value for the provided key in the preferences
 */
- (void)setObject:(nullable id)obj forKeyedSubscript:(nonnull LLMapViewPreferencesKey)key;

/**
 * gets the value with the key or returns nil if no value for the key
 */
- (nullable id)objectForKey:(nonnull LLMapViewPreferencesKey)key;
/**
 * provides a subscript access to get a value
 */
- (nullable id)objectForKeyedSubscript:(nonnull LLMapViewPreferencesKey)key;


@end
