//
//  LLConfiguration.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/17/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface LLConfiguration : NSObject

// Bundle Constants
@property (nonatomic, strong) NSString *sdkUrl;
@property (nonatomic, strong) NSString *assetsBase;
@property (nonatomic, strong) NSString *alphaAssetsBase;
@property (nonatomic, strong) NSString *betaAssetsBase;
@property (nonatomic, strong) NSString *gammaAssetsBase;
@property (nonatomic, strong) NSString *accountId;
@property (nonatomic, strong) NSString *alphaAccountId;
@property (nonatomic, strong) NSString *formatVersion;

/**
 * <code>assetsOverrideBundle</code> is a bundle that will get checked first for any LocusMaps SDK resources, before the LocusMaps
 * bundle. This allows for customization of resources, like images. They can be provided in a separate bundle or in the
 * application main bundle and will be loaded instead of the default resources.
 *
 * Please note that you can choose to override only a subset of images this way. Whatever is not present in <code>assetsOverrideBundle</code>
 * will be still loaded from the LocusMaps bundle.
 *
 */
@property (nonatomic, strong) NSBundle *assetsOverrideBundle;

@property (nonatomic, strong) NSString *sdkBundleName;
@property (nonatomic, readonly) NSBundle *sdkBundle; // this should be removed, if not used by customers...
@property (atomic) bool useBundle;
@property (atomic) bool cache;

@property (nonatomic, strong) NSDictionary *config;
@property (nonatomic, strong) NSString *key;
@property (nonatomic, strong) NSString *keyId;
@property (nonatomic) NSString *language;
@property (nonatomic) BOOL hours24format;

@property (nonatomic) BOOL recommendedPlacesEnabled DEPRECATED_MSG_ATTRIBUTE("this attribute is not used anymore");


// Remote Assets
@property (nonatomic, strong) NSString *poiImagesUrl;
@property (nonatomic, strong) NSString *poiImagesUrlTemplate;
@property (nonatomic, strong) NSString *poiImagesUrlTemplateCenterCrop;

// Fonts
@property (nonatomic, strong) UIFont *font;
@property (nonatomic, strong) UIFont *lightFont;
@property (nonatomic, strong) UIFont *boldFont;

// Colors
@property (nonatomic, strong) UIColor *textColor;
@property (nonatomic, strong) UIColor *darkTextColor;
@property (nonatomic, strong) UIColor *lightTextColor;
@property (nonatomic, strong) UIColor *linkColor;
@property (nonatomic, strong) UIColor *lightGrayBackgroundColor DEPRECATED_MSG_ATTRIBUTE("this attribute is not used anymore");
@property (nonatomic, strong) UIColor *blueBackgroundColor;
@property (nonatomic, strong) UIColor *defaultSearchBarBackgroundColor DEPRECATED_MSG_ATTRIBUTE("this attribute is not used anymore");
@property (assign) CGFloat poiAlphaChannel;
@property (nonatomic, strong) UIColor *sponsoredSearchResultBackgroundColor DEPRECATED_MSG_ATTRIBUTE("this attribute is not used anymore");

// String & Other Constants
@property (nonatomic, strong) NSString *cancelButtonLabel;
@property (nonatomic, strong) NSString *bottomBarNavigateButtonLabel DEPRECATED_MSG_ATTRIBUTE("this button has not title");
@property (nonatomic, strong) NSString *bottomBarVenuesButtonLabel DEPRECATED_MSG_ATTRIBUTE("this button is not used");
@property (nonatomic, strong) NSString *bottomBarAirportsButtonLabel DEPRECATED_MSG_ATTRIBUTE("use bottomBarVenuesButtonLabel");
@property (nonatomic, strong) NSString *bottomBarMyPositionButtonLabel DEPRECATED_MSG_ATTRIBUTE("this button has not title");
@property (nonatomic, strong) NSString *bottomBarLevelsButtonLabel DEPRECATED_MSG_ATTRIBUTE("this button has not title");
@property (nonatomic, strong) NSString *bottomBarGrabButtonLabel;
@property (nonatomic, strong) NSString *bottomBarVoucherButtonLabel;
@property (nonatomic, strong) NSNumber *currentLevelFadeDuration;
@property (nonatomic, strong) NSNumber *currentLevelFadeDelay;

// API Webservices
@property (nonatomic, strong) NSString *apiWebservicesUrl;

@property (nonatomic, strong) NSString *initialAirportCode;

+ (LLConfiguration *)sharedConfiguration;

+ (UIFont *)fontWithSize:(CGFloat)fontSize; // return the font in the given size
+ (UIFont *)lightFontWithSize:(CGFloat)size; // return the lightFont in the given size

+ (UIColor *)gray:(NSUInteger)zeroTo255;     // return a gray with the specified value (0-255) alpha: 1

// return a color with rgb each in the range 0-255 (alpha always set to 1)
+ (UIColor *)colorWithRed:(NSUInteger)red green:(NSUInteger)green blue:(NSUInteger)blue;

- (void)loadConfiguration;

- (void)loadConfigurationFrom:(NSString *)filename;

@property (nonatomic, readonly) NSURL *baseURL;

- (UIImage *)cachedImageFromSDKBundle:(NSString *)imageFilename;

- (NSString *)dataUriForImageFromSDKBundle:(NSString *)fileName;

- (void)clearCache;

@end
