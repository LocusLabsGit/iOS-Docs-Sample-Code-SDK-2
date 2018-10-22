//
//  LLThemeBuilder.h
//  LocusLabsSDK
//
//  Created by Sam Ziegler on 7/13/16.
//  Copyright © 2016 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLTheme;

/**
 * The LLThemeBuilder is used to create new LLThemes which can used to change the SDK's GUI properties.  To modify an existing theme,
 * you first create a new LLThemeBuilder based on the theme you want to modify then make calls to setProperty to change the appropriate values.  Once
 * you have changed all of the desired properties, you can retrieve the new theme via the object's theme property.  For Example, to change the default font:
 *   themeBuilder = [LLThemeBuilder themeBuilderWithTheme:[LLThemeBuilder defaultTheme]];
 *   [themeBuilder setProperty:@"fonts.normal" value:[UIFont systemFontOfSize:10]];
 *   newTheme = themeBuilder.theme;
 */
@interface LLThemeBuilder : NSObject

/**
 * Creates a new empty LLThemeBuilder object.
 */
+ (nonnull LLThemeBuilder *)themeBuilder;

/**
 * Creates a LLThemeBuilder object based on the provided theme.
 */
+ (nonnull LLThemeBuilder *)themeBuilderWithTheme:(nullable LLTheme *)theme;

/**
 * Appends all properties from given theme to the current theme. Overrides any existing properties.
 * @param theme to load the properties from
 */
- (nonnull LLThemeBuilder *)loadPropertiesFromTheme:(nonnull LLTheme *)theme;

/**
 * Change a theme property.
 * @param key the name of the property
 * @param value the new value, must be a NSNumber, NSString, UIFont or a UIColor
 */
- (nonnull LLThemeBuilder *)setProperty:(nonnull NSString *)key value:(nonnull NSObject *)value;

/**
 * The new theme.
 */
@property (readonly,nonatomic,strong,nonnull) LLTheme *theme;

@end
