//
//  LLPOI.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 7/24/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLPOIDataProtocol.h"

@class LLPosition;
@class LLFlight;

/**
 *  All of the available information about a POI.
 */
@interface LLPOI : NSObject <LLPOIData>

/**
 *  The unique identifier of this POI.
 */
@property (nonatomic, readonly) NSString *poiId;

/**
 *  A localized string identifying this POI which can be used for display purposes.
 */
@property (nonatomic, readonly) NSString *name;

/**
 *  The geographic position of the POI.
 */
@property (nonatomic, readonly) LLPosition *position;

/**
 *  The nearest gate to this POI, if applicable.
 */
@property (nonatomic, readonly) NSString *gate;

/**
 *  The operating terminal of this POI, if applicable.
 */
@property (nonatomic, readonly) NSString *terminal;

/**
 *  The URL associated with this POI.  For example, this may be a company website if the POI is a store.
 */
@property (nonatomic, readonly) NSString *url;

/**
 *  The visible value to display for the URL property. This could be the domain name or a proper name. Absence of this property will display the URL as "Website".
 */
@property (nonatomic, readonly) NSString *urlDisplay;

/**
 *	Additional attributes for the POI.
 */
@property (nonatomic, readonly) NSDictionary *additionalAttributes;

/**
 *  An icon for the POI.
 */
@property (nonatomic, readonly) NSString *icon;

/**
 *  Absolute URL of icon
 */
@property (nonatomic, readonly) NSURL *iconUrl;

/**
 *  An image of the POI.
 */
@property (nonatomic, readonly) NSString *image;

/**
 *  Additional images of the POI.
 */
@property (nonatomic, readonly) NSArray *additionalImages;

/**
 *  Absolute URL of image
 */
@property (nonatomic, readonly) NSURL *imageUrl;

/**
 *	Absolute URLs for all additional images
 */
@property (nonatomic, readonly) NSArray *additionalImageUrls;

/**
 *  An array of NSStrings which are used to classify this POI.
 */
@property (nonatomic, readonly) NSArray *tags;

/**
 *  Subset of the tags meant for display.
 */
@property (nonatomic, readonly) NSArray *displayTags;

/**
 *  The category that this POI is apart of.
 */
@property (nonatomic, readonly) NSString *category;

/**
 *  A localized description of this POI.
 */
@property (nonatomic, readonly) NSString *poiDescription;
@property (nonatomic, readonly) BOOL hasDescription;

/**
 *  A phone number for this POI, if applicable.
 */
@property (nonatomic, readonly) NSString *phone;

/**
 *  The operating hours of this POI, if applicable.
 */
@property (nonatomic, readonly) NSString *hours;

/**
 *  The operating venue of this POI, if applicable.
 *
 *  **Deprecated**: use venue
 */
@property (nonatomic, readonly) NSString *airport DEPRECATED_MSG_ATTRIBUTE("use venue");

/**
 *  The operating venue of this POI, if applicable.
 */
@property (nonatomic, readonly) NSString *venue;

/**
 *  Radius
 */
@property (nonatomic, readonly) NSNumber *radius;

/**
 *  Logo
 */
@property (nonatomic, readonly) NSString *logo;

/**
 *  Absolute URL of the logo
 */
@property (nonatomic, readonly) NSURL *logoUrl;



/**
 *  An arbitrary userLabel set in LLMapView.addUserPOI
 */
@property (nonatomic, strong) NSString *userLabel;

@property (nonatomic, strong) LLFlight *flight;

/**
 *  Properties used for POI display
 */
@property (nonatomic, readonly) NSDictionary *displayProperties;

/**
 An array of NSDictionary objects each of which has a 'days' and 'hours' field that indicates the
 operating hours of the POI for a part of the week
*/
// TODO [api] remove and mark as removed in the "migrating to 2.0" docs
//@property (nonatomic, readwrite) NSArray *operatingHours __attribute__((deprecated("replaced by detailedOperatingHours")));;

/**
 An array of 7 arrays (one for each week day) containing LLOperatingHours objects.
 A POI can be open for a variable number of blocks throughout a day, or none at all if it is closed.
 */
@property (nonatomic, readonly) NSArray *detailedOperatingHours;

/**
 Easy-to-check flag for whether or not this POI has a list of operating hours
 */
@property (nonatomic, readonly) BOOL hasOperatingHours;

/**
 * Indicates if the POI has any navigation directions.
 * If nil then the POI can be navigated to/from.
 * Otherwise if non-nil and true then the POI can NOT be navigated/from.
 */
@property (nonatomic, readonly) NSNumber *noDirections;

- (BOOL)isEqual:(id)object;

@property (nonatomic, readonly) NSUInteger hash;

@end
