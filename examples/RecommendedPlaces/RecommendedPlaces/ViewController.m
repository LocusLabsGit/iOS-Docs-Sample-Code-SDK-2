//
//  ViewController.m
//  RecommendedPlaces
//
//  Created by Juan Kruger on 18/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, strong) LLFloor           *floor;
@property (nonatomic, strong) LLMapView         *mapView;

@end

@implementation ViewController

#pragma mark Lifecycle

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
    [LLLocusLabs setup].accountId = @"A11F4Y6SZRXH4X";
    
    [LLConfiguration sharedConfiguration].recommendedPlacesEnabled = YES;
    
    // Get an instance of the LLVenueDatabase and register as its delegate
    self.venueDatabase = [LLVenueDatabase venueDatabase];
    self.venueDatabase.delegate = self;
    
    // Create a new LLMapView, register as its delegate and add it as a subview
    LLMapView *mapView = [[LLMapView alloc] init];
    self.mapView = mapView;
    self.mapView.delegate = self;
    [self.view addSubview:mapView];
    
    // Set the mapview's layout constraints
    mapView.translatesAutoresizingMaskIntoConstraints = NO;
    [mapView.leftAnchor constraintEqualToAnchor:self.view.leftAnchor].active = YES;
    [mapView.rightAnchor constraintEqualToAnchor:self.view.rightAnchor].active = YES;
    [mapView.topAnchor constraintEqualToAnchor:self.view.topAnchor].active = YES;
    [mapView.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor].active = YES;
    
    // Load the venue LAX
    [self.venueDatabase loadAirport:@"lax"];
}

#pragma mark Custom

- (NSArray *)customRecommendedPlaces {
    
    NSMutableArray *customPlaces = [NSMutableArray array];
    
    // Create a custom Recommended Place to show a POI
    LLPlaceUI *ui = [LLPlaceUI defaultUI];
    ui.icon = @"bottombar-icon-nav.png"; // Supply any solid fill png. This one chosen as it is already in the bundle - you can supply your own
    ui.normalIconColor = [UIColor whiteColor];
    ui.selectedIconColor = [UIColor whiteColor];
    ui.marker = @"images/nav-badge-bus.svg"; // This image chosen as it is already in the bundle - you can supply your own
    
    // POI 519 is gate 68A at lax
    LLPlace *customPOIRecommendedPlace = [[LLPlace alloc] initWithBehavior:LLPlaceBehaviorPOI values:@[@"519"] displayName:@"Departure Gate" andUI:ui];
    [customPlaces addObject:customPOIRecommendedPlace];
    
//    // Create a custom Recommended Place to trigger a search
//    LLPlaceUI *uiSearch = [LLPlaceUI defaultUI];
//    uiSearch.icon = @"bottombar-icon-nav.png";
//    uiSearch.normalIconColor = [UIColor whiteColor];
//    uiSearch.selectedIconColor = [UIColor whiteColor];
//    uiSearch.marker = @"images/nav-badge-bus.svg";
//    
//    LLPlace *customSearchRecommendedPlace = [[LLPlace alloc] initWithBehavior:LLPlaceBehaviorSearch values:@[@"magazines"] displayName:@"Magazines" andUI:uiSearch];
//    [customPlaces addObject:customSearchRecommendedPlace];
    
    return customPlaces;
}

#pragma mark Delegates - LLVenueDatabase

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString *)venueId code:(LLDownloaderError)errorCode message:(NSString *)message {
    
    // Handle failures here
}

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoaded:(LLVenue *)venue {
    
    // Store the loaded airport
    self.venue = venue;
    
    // Collect the list of buildingsInfos found in this airport and (arbitrarily) load the first one
    LLBuildingInfo *buildingInfo = [self.venue listBuildings][0];
    LLBuilding *building  = [self.venue loadBuilding:buildingInfo.buildingId];
    
    // Collect the list of floorInfos found in this building and (arbitrarily) load the first one
    LLFloorInfo *floorInfo = [building listFloors][0];
    self.floor = [building loadFloor:floorInfo.floorId];
    
    // Set all the delegates
    self.floor.delegate = self;
    
    // Load the map for the floor.  Map is sent via floor:mapLoaded:
    [self.floor loadMap];
}

#pragma mark Delegates - LLFloor

- (void)floor:(LLFloor *)floor mapLoaded:(LLMap *)map {
    
    self.mapView.map = map;
}

#pragma mark Delegates - LLMapView

- (void)mapViewDidClickBack:(LLMapView *)mapView {
    
    // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
}

- (void)mapViewReady:(LLMapView *)mapView {
    
    // The map is ready to be used in calls e.g. zooming, showing poi, etc.
}

- (NSArray *)mapView:(LLMapView *)mapView willPresentPlaces:(NSArray *)places {

    // Show only 1 recommended place
    // return @[places[0]];

    // Show default recommended places
    // return places;

    // Show only the tray button (when tapped - it will open the tray showing all recommended places)
    // return [@[[NSNull null]] arrayByAddingObjectsFromArray:places];

    // Show custom recommended places
    return [self customRecommendedPlaces];
}

- (NSArray<NSString*> *)mapView:(LLMapView *)mapView willPresentSearchSuggestions:(NSArray<NSString*> *)suggestions {
    
    return @[@"Restaurants", @"Bars", @"Pharmacies", @"Baggage"];
}

- (BOOL)mapView:(LLMapView *)mapView didTapPOI:(NSString *)poiId {

    return YES;
}



@end
