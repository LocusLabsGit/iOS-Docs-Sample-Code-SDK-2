//
//  ViewController.m
//  UserPositionSimulated
//
//  Created by Juan Kruger on 05/02/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, strong) LLFloor           *floor;
@property (nonatomic, weak)   LLMapView         *mapView;
@property (nonatomic, strong) LLPositionManager *positionManager;


@end

@implementation ViewController {
    
    BOOL initialZoomDone;
}

#pragma mark Lifecycle

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
    [LLLocusLabs setup].accountId = @"A11F4Y6SZRXH4X";
    
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
    [self.venueDatabase loadVenue:@"lax"];
}

#pragma mark Custom

- (NSDictionary *)locationDictWithLat:(NSNumber *)lat lon:(NSNumber *)lon {

    LLLatLng *latLng = [[LLLatLng alloc] initWithLat:lat lng:lon];
    NSDictionary *locationDict = @{@"latLng": latLng,
                                   @"errorRadius": @(1),
                                   @"floorId": @"lax-south-departures",
                                   @"heading": @(34)};
    
    return locationDict;
}

- (void)postUserPosition:(NSDictionary *)locationDict {
    
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_POSITION_SENSOR_POSITION_CHANGED
                                                        object:nil
                                                      userInfo:locationDict];
}

- (void)startTrackingUserPosition {
    
    self.positionManager = [[LLPositionManager alloc] initWithVenues:@[self.venue]];
    self.positionManager.delegate = self;
    
    // Start with passive positioning to conserve battery
    self.positionManager.passivePositioning = YES;
}

#pragma mark Delegates - LLVenueDatabase

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString *)venueId code:(LLDownloaderError)errorCode message:(NSString *)message {
    
    // Handle failures here
}

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoaded:(LLVenue *)venue {
    
    self.venue = venue;
    
    // Get a list of buildings in this airport and load the first one
    LLBuildingInfo *buildingInfo = [self.venue listBuildings][0];
    LLBuilding *building  = [self.venue loadBuilding:buildingInfo.buildingId];
    
    // Get a list of floors for the building and load the first one
    LLFloorInfo *floorInfo = [building listFloors][0];
    self.floor = [building loadFloor:floorInfo.floorId];
    
    // Set the floor delegate and load its map - mapLoaded is called when loading is complete
    self.floor.delegate = self;
    [self.floor loadMap];
}

#pragma mark Delegates - LLFloor

- (void)floor:(LLFloor *)floor mapLoaded:(LLMap *)map {
    
    self.mapView.map = map;
    self.mapView.positioningEnabled = YES;
}

#pragma mark Delegates - LLMapView

- (void)mapViewDidClickBack:(LLMapView *)mapView {
    
}

- (void)mapViewReady:(LLMapView *)mapView {

    // Set the navigation source to internal & send timed navigation points
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SET_POSITIONING_SENSOR_ALGORITHM
                                                        object:nil
                                                      userInfo:@{@"positioningSensorAlgorithm":@(LLPositioningSensorAlgorithmExternal)}];
    NSLog(@"FFF");
    // Position 1 (Initial - DFS Duty Free)
    NSDictionary *locationDict = [self locationDictWithLat:@33.941485 lon:@-118.40195];
    [self performSelector:@selector(postUserPosition:) withObject:locationDict afterDelay:0.0];
    
    // Position 2 (2 secs later)
    locationDict = [self locationDictWithLat:@33.941398 lon:@-118.401916];
    [self performSelector:@selector(postUserPosition:) withObject:locationDict afterDelay:2.0];
    
    // Position 3 (4 secs later)
    locationDict = [self locationDictWithLat:@33.941283 lon:@-118.401863];
    [self performSelector:@selector(postUserPosition:) withObject:locationDict afterDelay:4.0];
    
    // Position 4 (6 secs later)
    locationDict = [self locationDictWithLat:@33.941102 lon:@-118.401902];
    [self performSelector:@selector(postUserPosition:) withObject:locationDict afterDelay:6.0];
    
    // Position 5 (8 secs later - Destination - Gate 64B)
    locationDict = [self locationDictWithLat:@33.940908 lon:@-118.40177];
    [self performSelector:@selector(postUserPosition:) withObject:locationDict afterDelay:8.0];
}

#pragma mark Delegates - LLPositionManager

- (void)positionManager:(LLPositionManager *)positionManager positioningAvailable:(BOOL)positioningAvailable {
    
    if (positioningAvailable) {
        
        NSLog(@"Positioning available");
    }
    else {
        
        NSLog(@"Positioning not available - determine if bluetooth is active and prompt user if not.");
    }
}

- (void)positionManager:(LLPositionManager *)positionManager positionChanged:(LLPosition *)position {
    
    if (!position) {
        
        NSLog(@"Unable to locate user");
        return;
    }
    
    if (!initialZoomDone) {
    
        self.mapView.mapCenter = [[LLLatLng alloc] initWithLat:position.latLng.lat lng:position.latLng.lng];
        self.mapView.mapRadius = @50.0;
        initialZoomDone = YES;
    }
    
    // If we're near a venue, start active positioning (more battery intensive but provides accurate tracking)
    if (position.venueId) {
        
        self.positionManager.activePositioning = YES;
        NSLog(@"Near venueId: %@", position.venueId);
    }
}

@end
