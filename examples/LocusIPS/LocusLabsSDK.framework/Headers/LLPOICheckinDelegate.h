//
//  LLPOICheckinDelegate.h
//  LocusLabsSDK
//

#import <Foundation/Foundation.h>

/**
 * Represents the various states the Mobile Checkin Button can have in the POI Window.
 *
 * LLPOICheckinNoButton - The Mobile Checkin Button is not displayed.
 * LLPOICheckinDisabledButton - The Mobile Checkin Button is displayed but can not be tapped.
 * LLPOICheckinEnabledButton - The Mobile Checkin Button is displayed and is tappable.
 */
typedef NS_ENUM( NSInteger, LLPOICheckinButtonOptions ) {
    LLPOICheckinNoButton,
    LLPOICheckinDisabledButton,
    LLPOICheckinEnabledButton
};

/**
 * Callback block for poiCheckinEligibility method.
 * @param buttonOption How the checkin button should be displayed or not.
 */
typedef void (^POICheckinEligibilityBlock) (LLPOICheckinButtonOptions buttonOption);

/**
 * Callback block for successfully checking into a POI
 * @param checkinData Data to be used post checkin.
 *     The keys "code" and "name" are expected and displayed on the confirmation screen.
 */
typedef void (^POICheckinSuccessBlock) (NSDictionary *checkinData);

/**
 * Callback block for failing to checking into a POI.
 * @param failureTitle The title for the failure dialog that will be displayed.  Should be nil on success.
 * @param failureMessage The cause of the failure.  Should be nil on success.
 */
typedef void (^POICheckinFailureBlock) (NSString *failureTitle, NSString *failureMessage);


/**
 * Implementation of this protocol allows the POI Window to provide for a remote Mobile Checkin.
 */
@protocol LLPOICheckinDelegate <NSObject>

/**
 * This method will callback on the block the result of determining if checkin is allowed.
 */
- (void)poiCheckinEligibility:(POICheckinEligibilityBlock)block;

/**
 * @param poiCode The POI code to use for checking in.
 * @param guestCount number of guests to check in.
 * This method will callback on the block the result of checking in the user.
 */
- (void)poiCheckin:(NSString*)poiCode guests:(int)guestCount onPOICheckinSuccess:(POICheckinSuccessBlock)success onPOICheckinFailure:(POICheckinFailureBlock)failure;


@optional

/**
 * Dictionary containing configuration settings for
 * the various screens of the POI Checkin Process.
 *
 * Valid Keys include:
 * + checkinTitle - Title for the checkin screen.
 * + checkinMessage - Messaging for the checkin screen.
 * + confirmationTitle - Title for the checkin confirmation screen.
 * + confirmationMessage - Mesaging for the checkin confirmation screen.
 * + guestMessage - Messaging about number of guests allowed.
 * + notConnectedTitle - Title for the error dialog when the user is not connected.
 * + notConnectedMessage - Message for the error dialog when the user is not connected.
 * + noLocationServicesTitle - Title for the error dialog when the user does not have location services enabled.
 * + noLocationServicesMessage - Message for the error dialog when the user does not have location services enabled.
 * + notInRangeTitle - Title for the error dialog when the user is not close enough to the POI.
 * + notInRangeMessage - Message for the error dialog when the user is not close enough to the POI.
 * + maxGuests - Maximum number of guest the user can checkin.
 * + skipLocationServicesCheck - This key will skip the Location Services check.
 * + skipConnectedCheck - This key will skip the Connected check.
 * + skipGeofenceCheck - This key will skip the Geofence check.
 */
- (NSDictionary*)poiCheckinConfiguration;


@end
