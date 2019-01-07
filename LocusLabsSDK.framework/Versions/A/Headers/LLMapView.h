//
//  LLMapView.h
//  LocusLabsSDK
//
//  Created by Samuel Ziegler on 6/12/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "LLMapTips.h"
#import "LLMapViewDelegate.h"
#import "LLPosition.h"

@class LLVenue;
@class LLFlight;
@class LLFloorView;
@class LLInternalMapView;
@class LLMap;
@class LLPOI;
@class LLPositionManager;
@class LLTheme;
@class LLTopFillerDisplayController;
@class LLBottomFillerDisplayController;
@class LLMapViewUIController;

/**
 *  UIView for displaying LocusLabs floor maps.
 */
@interface LLMapView : UIView

/**
 *  The map to render.
 *
 * **Deprecated**: Setting the map property is deprecated and not fully supported. To display a map view create [LLVenueDatabase venueDatabaseWithMapView:]
 * and use [LLVenueDatabase loadVenueAndMap:block:] or [LLVenueDatabase loadVenueAndMap:initialSearch:iconUrl:block:]. This will configure the LLMapView map properly.
 */
@property (strong, nonatomic) LLMap *map;

// TODO [api] document as it's probably used in 1.6
@property (strong,nonatomic) UILabel *backLabel;

// TODO [api] document as removed
//@property (nonatomic, getter=shouldShowAirportsNav) BOOL showAirportsNav;

// TODO [api] document as it's probably used in 1.6
@property (nonatomic, getter=shouldShowMyPositionNav) BOOL showMyPositionNav;

// Hide me!
@property (strong,nonatomic) LLPositionManager *positionManager;

/**
 *  A delegate object to receive map events.
 */
@property (weak,nonatomic) id<LLMapViewDelegate> delegate;

/**
 *  Set the visibile radius around the center point.
 */
@property (nonatomic, strong) NSNumber *mapRadius;

/**
 *  Set the center point of the map view.
 */
@property (nonatomic, strong) LLLatLng *mapCenter;

/**
 * Set the user's current departing flight
 */
@property (strong,nonatomic) LLFlight *departingFlight;

/**
 * Display information about specific flights
 */
@property (strong,nonatomic) NSArray *flights;

/**
 * Should the LocusLabs UI include 20 extra pixels at the top to appear behind the status bar? Default: NO
 */
@property (nonatomic) BOOL shouldAllowSpaceForStatusBar;

/**
 * A disclaimer to presented to the user before showing them the result of the navigation.
 */
@property (strong,nonatomic) NSString *navigationDisclaimer;

// TODO [api] document as it's probably used in 1.6
@property (atomic) BOOL showNavButton;

/**
 * Allows the back button on the Search Header to be removed.
 * This makes the search bar itself bigger.
 * Default value: YES
 */
@property (nonatomic) BOOL showBackButton;

/**
 * Changes the POI window behavior to omit any missing information fields rather than printing "Unknown".
 * Deprecated. This value no longer affects anything and missing fields are always omitted.
 */
// TODO [api] remove and mark as removed in the "migrating to 2.0" docs
@property (nonatomic) BOOL hideMissingPOIInfo DEPRECATED_ATTRIBUTE;

/**
 * The venue associated with this map.
 *
 * **Deprecated**: use venue
 */
@property (readonly,nonatomic) LLVenue *airport DEPRECATED_MSG_ATTRIBUTE("use venue");

/**
 * The venue associated with this map.
 */
@property (readonly,nonatomic) LLVenue *venue;

/**
 *  A LLMapView is created to render a map within the given frame.
 *
 *  @param frame the view frame
 *
 *  @return self
 */
- (id)initWithFrame:(CGRect)frame;

/**
 * Zoom to and display the header popup view for the given POI.  The
 * map will switch levels if necessary.
 * This function does nothing if a bad or non-existent POI is given.
 *
 * @param poiId The id of the POI to show.
 */
- (void)showPoiByPoiId:(NSString *)poiId;

/**
 * Zoom to and display the header popup view for the given POI.  The
 * map will switch levels if necessary.
  *
 * @param poi The POI object to show.
 */
- (void)showPoi:(LLPOI *)poi;


// TODO [api] document as it's probably used in 1.6
- (void)didTapMarker:(LLMarker *)marker;

// TODO [api] document removed in 2.0
//- (void)didBeginDraggingMarker:(LLMarker *)marker;
// TODO [api] document removed in 2.0
//- (void)didEndDraggingMarker:(LLMarker *)marker;
// TODO [api] document removed in 2.0
//- (void)didDragMarker:(LLMarker *)marker;


- (void)mapViewReady;

/**
 * The LocusLabs SDK’s track an internal “session id” (a cryptographically correct UUID) to track user activity while using our maps.
 * A session is created as part of loading a map. When a user does something “interesting” on a map (move, view a POI, etc)
 * the app sends data to our analytics database associated with the session id.
 *
 * This property is available once the map view is ready.
 *
 * @return session id
 */
@property (nonatomic, readonly) NSString* sessionId;

// TODO [api] document as it's probably used in 1.6
- (void)levelSelected:(NSString*)levelName;

/**
 * Returns floor view for current level
 * @return floor view
 *
 * **Deprecated**: LLFloorView is deprecated, use floorId for overlays"
 */
- (LLFloorView*)getFloorViewForCurrentLevel __attribute__((deprecated("LLFloorView is deprecated, use floorId for overlays")));

/**
 * Returns floor view for given floor id
 * @return floor view
 *
 * **Deprecated**: LLFloorView is deprecated, use floorId for overlays"
 */
- (LLFloorView*)getFloorViewForId:(NSString*)floorId __attribute__((deprecated("LLFloorView is deprecated, use floorId for overlays")));

// TODO [api] document as it's probably used in 1.6
- (void)addUserPOI:(LLPOI*)poi userLabel:(NSString*)label;
// TODO [api] document as it's probably used in 1.6
- (void)removeUserPOI:(LLPOI*)poi;
// TODO [api] document as it's probably used in 1.6
- (void)navigateFromStart:(LLPosition*)start end:(LLPosition*)end;

/**
 * Programmatically open the navigation dialog passing in (optional) start and end positions
 */
-(void)openNavigationViewWithStart:(LLPosition*)navStart andEnd:(LLPosition*)navEnd;

/**
 * Programmatically cancel the user initiated navigation.
 */
- (void)cancelUserNavigation;

/**
 * Programmatically cancel user initiated search.
 */
- (void)cancelUserSearch;

- (void)initializeInternalMapView:(LLInternalMapView*)internalMapView;

/**
 * **Deprecated**: use initializeVenue:
 */
- (void)initializeAirport:(LLVenue*)venue DEPRECATED_MSG_ATTRIBUTE("use initializeVenue:");
- (void)initializeVenue:(LLVenue*)venue;

- (void)teardown;

// TODO [raho] theming !!! or set on LLSearchBarDisplayController
/**
 * Set the background color of the entire search bar
 */
- (void)setSearchBarBackgroundColor:(UIColor*)backgroundColor;

/**
 * Optional background image to display behind the search bar
 */
@property (strong,nonatomic) UIImage *searchBarBackgroundImage;


/**
 * Set the color of the cancel button in the search bar
 */
- (void)setSearchBarCancelButtonColor:(UIColor*)cancelButtonColor;

/**
 * Change the back button's text
 */
- (void)setBackButtonText:(NSString*)backButtonText;

/**
 * Get/set the color of the back button text.
 */
@property (nonatomic, strong) UIColor *backButtonTextColor;

- (void) runMemoryTests;

/**
 * If set to YES, whenever the user is first located the follow me mode will be enabled and the map will be centered on the user position.
 * If set to NO, there will be no jump to user position when it's first found, but user will be still able to enable follow me mode manually.
 *
 * Default is YES.
 */
@property (nonatomic) BOOL startInFollowMeMode;

/**
 * Toggles the use of positioning to display the user's current position on the map.  Default is YES.
 */
@property (nonatomic) BOOL positioningEnabled;
@property (nonatomic) BOOL shouldShowClosestBeacon;

/**
 * Hide/show the search bar.  Default is NO.
 */
@property (nonatomic) BOOL searchBarHidden;

/**
 * Hide/show the bottom bar.  Default is NO.
 */
@property (nonatomic) BOOL bottomBarHidden;

/**
 * Hide/show the recommended places buttons.  Default is NO.
 */
@property (nonatomic) BOOL recommendedPlacesHidden;

/**
 * Loading map state.
 */
@property (nonatomic, readonly, getter=isLoadingMap) BOOL loadingMap;

/**
 * Loading directions state.
 */
@property (nonatomic, readonly, getter=isLoadingDirections) BOOL loadingDirections;

/**
 * Directions would be loaded. If set to yes the map will change it's status to loadingDirections=YES, immediately
 * after loadingMap has finished and was switched to NO. By Default it's NO.
 */
@property (nonatomic) BOOL willInitializeDirections;

/**
 * This property controls whether structure labels (like building, terminal labels) are enabled or not.
 * If set to <code>YES</code> the structure labels will be enabled and shown if the map view is zoomed out.
 * If set to <code>NO</code> the structure labels will be hidden, no matter the zoom level.
 *
 * By default it's set to <code>YES</code>
 */
@property (nonatomic) BOOL structureLabelsEnabled;

/**
 * This property controls whether the compass is shown when the map is not facing North.
 *
 * By default it's set to <code>YES</code>.
 */
@property (nonatomic) BOOL compassEnabled;

@property (retain,nonatomic) UINavigationController *mapTipsNavigationController;
@property (nonatomic) LLMapTipsPopupMethod mapTipsPopupMethod;

/**
 * Get or set the theme used by this LLMapView.
 */
@property (strong,nonatomic) LLTheme *theme;

/**
 * Triggers the reload of places from the venue data, which in turn causes the LLMapViewDelegate willPresentPlaces method to be called again
 */
- (void)refreshPlaces;

/**
 * When highlighting POIs the map is grayed out using this parameter to control the greyscale intensity to make it darker or lighter.
 * It can take any value from [0, 1], where 0 makes the background black.
 */
@property (nonatomic, strong) NSNumber *desaturationGreyscale;

@end
