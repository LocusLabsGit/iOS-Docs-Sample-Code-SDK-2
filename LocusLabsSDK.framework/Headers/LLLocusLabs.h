//
//  LLLocusLabs.h
//  LocusLabsSDK
//
//  Created by Glenn Dierkes on 1/23/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LLLocusLabsDelegate.h"
#import "LLPOICheckinDelegate.h"

@protocol GrabClientInterface;

@class LLPerson;

/**
 * This class is used for setting up the LocusLabs SDK.  It has a singleton instance which is accessed via the +(LLLocusLabs *)setup method.
 * Before any other SDK methods are called, the accountId property must be set.
 */
@interface LLLocusLabs : NSObject

/**
 * The delegate used to manage POI Checkins.
 */
@property (nonatomic, retain) id<LLPOICheckinDelegate> poiCheckinDelegate;

/**
 * The account id the SDK should use to interact with the LocusLabs resources.
 */
@property (nonatomic, retain) NSString *accountId;

/**
 * Returns the Install ID, an identifier associated with server-side event logging for user analytics.
 *
 * Please note that installId depends on the currently set <code>accountId</code>.
 * Please also note that installId might not be available right after assigning accountId as this value if provided by the server-side.s
 */
@property (nonatomic, readonly) NSString *installId;

/**
 * The user's IDFA for analytics tracking.
 */
@property (nonatomic, retain) NSUUID *idfa;

/**
 * Sets the LLLocusLabsDelegate
 */
@property (weak,nonatomic) id<LLLocusLabsDelegate> delegate;

/**
 * The Grab customer ID. If nil, Grab will not be loaded.
 */
@property (nonatomic) NSString *grabCustomerId;

/**
 * Optional dictionary defining styles for Grab.
 */
@property (nonatomic) NSDictionary *grabStyleDictionary;

/**
 * The presenting navigation controller
 */
@property (nonatomic, weak) UINavigationController *grabNavigationController;

/**
 * Positiong/Location Accuracy setting
 * Setting this to YES allows the SDK to track the users position/location at the highest
 * level of accuracy.  This also drains the battery more quickly.
 *
 * Default setting is NO.
 */
@property (nonatomic) BOOL useBestForNavigation;

/**
 * Setting this to YES allows the SDK to use the heading derived from Core Location.
 * Otherwise the heading is calculated via change in position.
 *
 * Default setting is YES.
 */
@property (nonatomic) BOOL useHeading;

/**
 * Setting this to YES disables "Follow-Me Mode" with regard to position updates.
 * It does not impact the UI.
 *
 * Default is NO.
 */
@property (nonatomic) BOOL disableFollowMeMode;

/**
 * Delay between position updates.  Default is 1.9 seconds.
 *
 * When in Follow-Me Mode the amount of time before a new position update is accepted.
 */
@property (nonatomic, retain) NSNumber *positionUpdatesDelay;


/**
 * In order to track the user's location the LocusLabs SDK must ask the user for permission to use location services.
 * There are (currently) two possible types of permission to request:
 *
 * - "when in use"
 * - "always"
 */
typedef NS_ENUM(unsigned long, LLLocationAuthorizationPermissionToRequest) {
    LLLocationAuthorizationPermissionToRequestAlways,
    LLLocationAuthorizationPermissionToRequestWhenInUse
};

/**
 * Set the permission that the SDK will request when asking the user for permission to use location services
 */
@property (nonatomic) LLLocationAuthorizationPermissionToRequest locationAuthorizationPermissionToRequest;

/**
 * Returns the SDK version string.
 */
+ (NSString *)version;

/**
 * Returns the LLLocusLabs singleton.
 * @returns the singleton
 */
+ (LLLocusLabs*)setup;

- (NSString*)assetsFormatVersion;

+ (void)reset;

/**
 * Log a person in, associating them with this install of the SDK.
 */
- (void)login:(LLPerson *)person;

/**
 * Log a person out, removing their association with this install of the SDK.
 */
- (void)logout:(LLPerson *)person;

@end
