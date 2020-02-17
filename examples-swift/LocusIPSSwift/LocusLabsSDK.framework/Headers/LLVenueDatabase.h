//
//  Created by Samuel Ziegler on 6/12/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "LLVenue.h"

@class LLVenueDatabase;
@compatibility_alias LLAirportDatabase LLVenueDatabase;
@class LLMap;
@class LLMapView;
@class LLMarker;

typedef enum _LLDownloaderError
{
    ACCOUNT_NOT_FOUND = 0,
    VENUE_NOT_FOUND,
    CORRUPTED_VENUE_DATA,
    UNABLE_TO_STORE_FILE_LOCALLY,
    FILE_NOT_DOWNLOADED_CORRECTEDLY,
    DOWNLOAD_FAILURE
} LLDownloaderError;
/**
 *  Delegates for LLVenueDatabase should implement this protocol.
 */
@protocol LLVenueDatabaseDelegate <NSObject>

@optional

/**
 *  Called with the data returned by the listVenues: method.
 *
 *  @param venueDatabase  the database instance which generated the call
 *  @param venueList      an array of LLVenueInfo instances
 */
- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueList:(NSArray *)venueList;

/**
 *  Called when no venueList could be returned by listVenues
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param reason the reason for the failure
 */
- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueListFailed:(NSString *)reason;

/**
 *  Called once a venue has been loaded via the loadVenue: method.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venue         the venue
 */
- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoaded:(LLVenue *)venue;

/**
 *  Called once a venue begun downloading maps and other necessary assets.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 */
- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadStarted:(NSString*)venueId;

/**
 *  Called once a venue has completed downloading maps and other necessary assets.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 */
- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadCompleted:(NSString*)venueId;

/**
 *  Called during asset downloads to give a progress update.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 *  @param percent       the percent download complete
 */
- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadStatus:(NSString*)venueId percentage:(int)percent;

/**
 *  Called if an error is encountered while downloading the venue maps.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 *  @param errorCode     the code for the failure
 *  @param message       the message for the failure
 */
- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString*)venueId code:(LLDownloaderError)errorCode message:(NSString*)message;

@end

/**
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
__attribute__((deprecated("use LLVenueDatabaseDelegate")))
@protocol LLAirportDatabaseDelegate <LLVenueDatabaseDelegate>

@optional

/**
 *  Called with the data returned by the listVenues: method.
 *
 *  @param venueDatabase  the database instance which generated the call
 *  @param venueList      an array of LLVenueInfo instances
 *
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
- (void)airportDatabase:(LLVenueDatabase *)venueDatabase airportList:(NSArray *)venueList __attribute__((deprecated("use LLVenueDatabaseDelegate")));

/**
 *  Called when no venueList could be returned by listVenues
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param reason the reason for the failure
 *
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
- (void)airportDatabase:(LLVenueDatabase *)venueDatabase airportListFailed:(NSString *)reason __attribute__((deprecated("use LLVenueDatabaseDelegate")));

/**
 *  Called once a venue has been loaded via the loadVenue: method.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venue         the venue
 *
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
- (void)airportDatabase:(LLVenueDatabase *)venueDatabase airportLoaded:(LLVenue *)venue __attribute__((deprecated("use LLVenueDatabaseDelegate")));

/**
 *  Called once a venue begun downloading maps and other necessary assets.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 *
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
- (void)airportDatabase:(LLVenueDatabase *)venueDatabase airportLoadStarted:(NSString*)venueId __attribute__((deprecated("use LLVenueDatabaseDelegate")));

/**
 *  Called once a venue has completed downloading maps and other necessary assets.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 *
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
- (void)airportDatabase:(LLVenueDatabase *)venueDatabase airportLoadCompleted:(NSString*)venueId __attribute__((deprecated("use LLVenueDatabaseDelegate")));

/**
 *  Called during asset downloads to give a progress update.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 *  @param percent       the percent download complete
 *
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
- (void)airportDatabase:(LLVenueDatabase *)venueDatabase airportLoadStatus:(NSString*)venueId percentage:(int)percent __attribute__((deprecated("use LLVenueDatabaseDelegate")));

/**
 *  Called if an error is encountered while downloading the venue maps.
 *
 *  @param venueDatabase the database instance which generated the call
 *  @param venueId       the venue id
 *  @param errorCode     the code for the failure
 *  @param message       the message for the failure
 *
 * **Deprecated**: use LLVenueDatabaseDelegate
 */
- (void)airportDatabase:(LLVenueDatabase *)venueDatabase airportLoadFailed:(NSString*)venueId code:(LLDownloaderError)errorCode message:(NSString*)message __attribute__((deprecated("use LLVenueDatabaseDelegate")));

@end

/**
 *  LLVenueDatabase is the primary entry point for all the LocusLabs venue functionality.
 *  To recieve any of the asynchronously generated data generated by this class,
 *  you must assign a delegate that implements the methods of the LLVenueDatabaseDelegate protocol.
 *
 *  Please note that for backward compatibility reasons this class can still be referenced as LLAirportDatabase, but the
 *  **LLAirportDatabase is deprecated** and will be removed in future releases.
 */
@interface LLVenueDatabase : NSObject

typedef void (^VenueAndMapLoadedBlock) (LLVenue *venue, LLMap *map, LLFloor *floor, LLMarker *marker);
typedef void (^GetLatestAssetVersionBlock) (NSString *version, NSString *errorMessage);
typedef void (^IsVenueOnPhoneBlock) (BOOL venueOnPhone);
typedef void (^IsVenueAvailableOnDeviceBlock) (BOOL airportAvailable);

/**
 * **Deprecated**
 */
typedef VenueAndMapLoadedBlock AirportAndMapLoadedBlock;
/**
 * **Deprecated**
 */
typedef IsVenueAvailableOnDeviceBlock IsAirportAvailableOnDeviceBlock;

/**
 *  Delegate for this instance
 */
@property (weak, nonatomic) id<LLVenueDatabaseDelegate> delegate;

/**
 *  Create an instance of LLVenueDatabase
 *
 *  @return the new venue database object
 *
 * **Deprecated**: use venueDatabase
 */
+ (LLVenueDatabase *)airportDatabase __attribute__((deprecated("use venueDatabase")));

/**
 *  Create an instance of LLVenueDatabase to operate on a venue in a "headless" mode = if no map view is to be displayed.
 *
 *  @return the new venue database object
 */
+ (LLVenueDatabase *)venueDatabase;

/**
 *  Create an instance of LLVenueDatabase for a specific MapView
 *
 *  @return the new venue database object
 *
 * **Deprecated**: use venueDatabaseWithMapView
 */
+ (LLVenueDatabase *)airportDatabaseWithMapView:(LLMapView*)mapView;
/**
 *  Create an instance of LLVenueDatabase for a specific LLMapView
 *
 *  @return the new venue database object
 */
+ (LLVenueDatabase *)venueDatabaseWithMapView:(LLMapView*)mapView;

/**
 *  Retrieve the list of venues available in the LocusLabs venue database.  The result will be returned via the
 *  venueDatabase:venueList: delegate method.
 *
 * **Deprecated**: use listVenues
 */
- (void)listAirports __attribute__((deprecated("use listVenues")));

/**
 * **Deprecated**: use listVenuesForLocale
 */
- (void)listAirportsForLocale:(NSString*)locale __attribute__((deprecated("use listVenuesForLocale")));

/**
 *  Retrieve the list of venues available in the LocusLabs venue database.  The result will be returned via the
 *  venueDatabase:venueList: delegate method.
 */
- (void)listVenues;

- (void)listVenuesForLocale:(NSString*)locale;

/**
 *  Load a specific venue.  The result will be returned to the delegate via venueDatabase:venueLoaded:
 *  Only 4 concurrent loadVenues can be handled simultaneously.  Doing more than 4 could result in load failures.
 *
 *  @param venueId identifies the venue to load
 *
 * **Deprecated**: use loadVenueAndMap:
 */
- (void)loadAirport:(NSString *)venueId __attribute__((deprecated("use loadVenueAndMap:")));

/**
 *  Load a specific venue.  The result will be returned to the delegate via venueDatabase:venueLoaded:
 *  Only 4 concurrent loadVenues can be handled simultaneously.  Doing more than 4 could result in load failures.
 *
 *  **Warning**: this method should only be used for "headless" mode of interaction with the SDK. So it only should be used
 *  if **LLMapView is not used**. If the intention is to display the map in the LLMapView use [LLVenueDatabase loadVenueAndMap:block:] or
 *  [LLVenueDatabase loadVenueAndMap:initialSearch:iconUrl:block:] instead.
 *  Using this method when LLVenueDatabase was initiated with [LLVenueDatabase venueDatabaseWithMapView:] is not supported.
 *
 *  @param venueId identifies the venue to load
 */
- (void)loadVenue:(NSString *)venueId;

/**
 * Has the map data for the specified venueId already been downloaded to the phone?
 *
 * Note: no information is returned about whether the version on the phone is the most up-to-date version
 */
- (void)isVenueOnPhone:(NSString*)venueId block:(IsVenueOnPhoneBlock)block;

typedef NS_ENUM(NSInteger, LLVenueDownloadConstraint) {
    LLVenueDownloadConstraintDownloadViaWifiOrPhone = 0,
    LLVenueDownloadConstraintDownloadOnlyViaWifi = 1,
    LLVenueDownloadConstraintDisallowDownloading = 2,
    LLAirportDownloadConstraintDownloadViaWifiOrPhone __attribute__((deprecated)) = LLVenueDownloadConstraintDownloadViaWifiOrPhone,
    LLAirportDownloadConstraintDownloadOnlyViaWifi __attribute__((deprecated)) = LLVenueDownloadConstraintDownloadOnlyViaWifi,
    LLAirportDownloadConstraintDisallowDownloading __attribute__((deprecated)) = LLVenueDownloadConstraintDisallowDownloading,
};

/**
 * **Deprecated**
 */
typedef LLVenueDownloadConstraint LLAirportDownloadConstraint;

/**
 *
 */
@property (nonatomic, assign) LLVenueDownloadConstraint downloadConstraint;

/**
 *  @param venueId identifies the venue to load
 *  @param initialSearch is a search string to zoom into as an initial position
 *
 * **Deprecated**: use loadVenueAndMap:initialSearch:iconUrl:block:
 */
- (void)loadAirportAndMap:(NSString *)venueId initialSearch:(NSString *)initialSearch iconUrl:(NSString*)iconUrl block:(VenueAndMapLoadedBlock)block __attribute__((deprecated("use loadVenueAndMap:initialSearch:iconUrl:block:")));

/**
 *  @param venueId identifies the venue to load; zooms to venue's default center and radius
 *
 * **Deprecated**: use loadVenueAndMap:block:
 */
- (void)loadAirportAndMap:(NSString *)venueId block:(VenueAndMapLoadedBlock)block __attribute__((deprecated("use loadVenueAndMap:block:")));

/**
 *  @param venueId identifies the venue to load
 *  @param initialSearch is a search string to zoom into as an initial position
 */
- (void)loadVenueAndMap:(NSString *)venueId initialSearch:(NSString *)initialSearch iconUrl:(NSString*)iconUrl block:(VenueAndMapLoadedBlock)block;

/**
 *  Load a specific venue.  The result will be returned to the delegate via venueDatabase:venueLoaded:
 *  Only 4 concurrent loadVenues can be handled simultaneously.  Doing more than 4 could result in load failures.
 *
 *  @param venueId identifies the venue to load; zooms to venue's default center and radius
 */
- (void)loadVenueAndMap:(NSString *)venueId block:(VenueAndMapLoadedBlock)block;

/**
 * Returns the latest version for the given venueId.
 * The latest venue id is retrieved by checking the latest available content on the server.
 * If the function is unable to connect to the server or the venueId is bad a 
 * non-nil "errorMessage" will be returned.
 *
 *  @param venueId the venue to check
 */
- (void)getLatestAssetVersion:(NSString *)venueId block:(GetLatestAssetVersionBlock)block;

/**
 * Downloads from the server the latest content for the given venueId.
 *
 * The delegate methods venueLoadStarted, venueLoadCompleted, venueLoadStatus and venueLoadFailed will be called.
 *
 *  @param venueId the venueId to be downloaded
 *
 * **Deprecated**: use downloadLatestVenue:
 */
- (void)downloadLatestAirport:(NSString *)venueId __attribute__((deprecated("use downloadLatestVenue:")));

/**
 * Downloads from the server the latest content for the given venueId.
 *
 * The delegate methods venueLoadStarted, venueLoadCompleted, venueLoadStatus and venueLoadFailed will be called.
 *
 *  @param venueId the venueId to be downloaded
 */
- (void)downloadLatestVenue:(NSString *)venueId;

/**
 * Checks if the given venueId is on the device for the specific version.
 * If version is null, then checks if any version of the venueId is on the device.
 *
 * **Deprecated**: use isVenueAvailableOnDevice:forVersion:block:
 */
- (void)isAirportAvailableOnDevice:(NSString*)venueId forVersion:(NSString*)version block:(IsAirportAvailableOnDeviceBlock)block __attribute__((deprecated("use isVenueAvailableOnDevice:forVersion:block:")));

/**
 * Checks if the given venueId is on the device for the specific version.
 * If version is null, then checks if any version of the venueId is on the device.
 */
- (void)isVenueAvailableOnDevice:(NSString*)venueId forVersion:(NSString*)version block:(IsVenueAvailableOnDeviceBlock)block;

/**
 * Returns the Install ID, an identifier associated with server-side event logging for user analytics.
 *
 * **Deprecated**: use LLLocusLabs installId property instead
 */
- (void)getInstallId:(void (^)(NSString *installId))block __attribute__((deprecated("use LLLocusLabs installId property instead ")));

// "private" in the sense that our customers shouldn't need to call this directly
- (void) teardown;

@end

