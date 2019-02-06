//
//  LLVenueInfo.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/12/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  The basic information about a venue as returned by the LLVenueDatabase listVenues: method.
 *
 *  Please note that for backward compatibility reasons this class can still be referenced as LLAirportInfo, but the
 *  **LLAirportInfo is deprecated** and will be removed in future releases.
 */
@interface LLVenueInfo : NSObject

/**
 *  The venue identifier.  This is used to create an instance of the LLVenue class via the LLVenueDatabase loadVenue: method.
 */
@property (retain, nonatomic) NSString *venueId;

/**
 *  The localized name of this venue.
 */
@property (retain, nonatomic) NSString *name;

/**
 *  The airport code
 */
@property (retain, nonatomic) NSString *airportCode;

/**
 *  The locale
 */
@property (retain, nonatomic) NSString *locale;

@end

@compatibility_alias LLAirportInfo LLVenueInfo;
