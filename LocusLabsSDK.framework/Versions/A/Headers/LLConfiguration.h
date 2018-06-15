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
@property (strong,nonatomic) NSString *sdkUrl;
@property (strong,nonatomic) NSString *assetsBase;
@property (strong,nonatomic) NSString *alphaAssetsBase;
@property (strong,nonatomic) NSString *betaAssetsBase;
@property (strong,nonatomic) NSString *gammaAssetsBase;
@property (strong,nonatomic) NSString *accountId;
@property (strong,nonatomic) NSString *alphaAccountId;
@property (strong,nonatomic) NSString *formatVersion;
@property (strong,nonatomic) NSString *sdkBundleName;
@property (atomic) bool useBundle;
@property (atomic) bool cache;
@property (strong,nonatomic) NSDictionary *config;
@property (strong,nonatomic) NSString *key;
@property (strong,nonatomic) NSString *keyId;
@property (nonatomic) NSString *language;
@property (nonatomic) BOOL hours24format;

/**
 * Enable/disable recommended places feature. The default value is <code>NO<code>
 */
@property (nonatomic) BOOL recommendedPlacesEnabled;


// Remote Assets
@property (strong,nonatomic) NSString *poiImagesUrl;
@property (strong,nonatomic) NSString *poiImagesUrlTemplate;
@property (strong,nonatomic) NSString *poiImagesUrlTemplateCenterCrop;

// Fonts
@property (strong,nonatomic) UIFont *font;
@property (strong,nonatomic) UIFont *lightFont;
@property (strong,nonatomic) UIFont *boldFont;

// Colors
@property (strong,nonatomic) UIColor *textColor;
@property (strong,nonatomic) UIColor *darkTextColor;
@property (strong,nonatomic) UIColor *lightTextColor;
@property (strong,nonatomic) UIColor *linkColor;
@property (strong,nonatomic) UIColor *lightGrayBackgroundColor;
@property (strong,nonatomic) UIColor *blueBackgroundColor;
@property (strong,nonatomic) UIColor *defaultSearchBarBackgroundColor;
@property (assign) CGFloat poiAlphaChannel;
@property (strong,nonatomic) UIColor *sponsoredSearchResultBackgroundColor;

// String & Other Constants
@property (strong,nonatomic) NSString *cancelButtonLabel;
@property (strong,nonatomic) NSString *bottomBarNavigateButtonLabel;
@property (strong,nonatomic) NSString *bottomBarVenuesButtonLabel;
@property (strong,nonatomic) NSString *bottomBarAirportsButtonLabel DEPRECATED_MSG_ATTRIBUTE("use bottomBarVenuesButtonLabel");
@property (strong,nonatomic) NSString *bottomBarMyPositionButtonLabel;
@property (strong,nonatomic) NSString *bottomBarLevelsButtonLabel;
@property (strong,nonatomic) NSString *bottomBarGrabButtonLabel;
@property (strong,nonatomic) NSString *bottomBarVoucherButtonLabel;
@property (strong,nonatomic) NSNumber *currentLevelFadeDuration;
@property (strong,nonatomic) NSNumber *currentLevelFadeDelay;

// API Webservices
@property (strong,nonatomic) NSString *apiWebservicesUrl;

@property (strong,nonatomic) NSString *initialAirportCode;

+ (LLConfiguration *)sharedConfiguration;
+ (UIFont *) fontWithSize:(CGFloat)fontSize; // return the font in the given size
+ (UIFont*) lightFontWithSize:(CGFloat)size; // return the lightFont in the given size

+ (UIColor*) gray:(NSUInteger)zeroTo255;     // return a gray with the specified value (0-255) alpha: 1

// return a color with rgb each in the range 0-255 (alpha always set to 1)
+ (UIColor*) colorWithRed:(NSUInteger)red green:(NSUInteger)green blue:(NSUInteger)blue;

- (void)loadConfiguration;
- (void)loadConfigurationFrom:(NSString *)filename;

@property (nonatomic,readonly) NSBundle *sdkBundle;
@property (nonatomic,readonly) NSURL *baseURL;

- (UIImage *)cachedImageFromSDKBundle:(NSString *)imageFilename;
- (NSString*)dataUriForImageFromSDKBundle:(NSString*)fileName;

- (void)clearCache;

@end
