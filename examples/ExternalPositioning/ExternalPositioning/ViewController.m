//
//  ViewController.m
//  ExternalPositioning
//
//  Created by Juan Kruger on 05/02/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, weak)   LLMapView         *mapView;

- (NSDictionary *)locationDictWithLat:(NSNumber *)lat lon:(NSNumber *)lon floorId:(NSString *)floorId heading:(NSNumber *)heading;
- (NSString *)locusLabsFloorIDForExternalFloorID:(NSString *)externalFloorId;
- (void)mockExternalLocationData;
- (void)postUserPosition:(NSDictionary *)locationDict;

@end

@implementation ViewController {
    
}

#pragma mark Lifecycle

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
    [LLLocusLabs setup].accountId = @"A11F4Y6SZRXH4X";
    
    // Create a new LLMapView, register as its delegate and add it as a subview
    LLMapView *mapView = [[LLMapView alloc] initWithFrame:self.view.bounds];
    mapView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    mapView.delegate = self;
    [self.view addSubview:mapView];
    
    self.mapView = mapView;
    self.mapView.showTopSafeAreaOverlay = NO;
    
    // Get an instance of LLVenueDatabase, set it's mapview and register as its delegate
    self.venueDatabase = [LLVenueDatabase venueDatabaseWithMapView:self.mapView];
    self.venueDatabase.delegate = self;
    
    // Load the venue LAX async
    [self.venueDatabase loadVenueAndMap:@"lax" block:^(LLVenue *venue, LLMap *map, LLFloor *floor, LLMarker *marker) {
        
        self.venue = venue;
        self.venue.delegate = self;
        
        // Use the method below to obtain a list of all buildings and associated floors in the venue.
        // Results are delivered in the floorList delegate method and can be used to create a mapping table between the floor ids of
        // the external positioning provider and the LocusLabs floor ids which needs to be done before delivering location data to our SDK
        // [self.venue listBuildings];
        
        // Set the navigation source to external
        [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SET_POSITIONING_SENSOR_ALGORITHM
                                                            object:nil
                                                          userInfo:@{@"positioningSensorAlgorithm":@(LLPositioningSensorAlgorithmExternal)}];
    }];
}

#pragma mark Custom

- (void)hideBlueDot {
    
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_POSITION_CLEAR object:nil];
}

- (NSDictionary *)locationDictWithLat:(NSNumber *)lat lon:(NSNumber *)lon floorId:(NSString *)floorId heading:(NSNumber *)heading {

    if (!heading) heading = @(1);
    
    LLLatLng *latLng = [[LLLatLng alloc] initWithLat:lat lng:lon];
    NSDictionary *locationDict = @{@"latLng": latLng,
                                   @"errorRadius": @(1),
                                   @"floorId": floorId,
                                   @"heading": heading}; // heading is optional
    
    return locationDict;
}

- (NSString *)locusLabsFloorIDForExternalFloorID:(NSString *)externalFloorId {
    
    // If you are not able to compile this mapping table yourself, please send us a list (help@locuslabs.com) of
    // the building names and associated floor ids as provided by your external mapping provider and we will compile the mapping table
    // To obtain a list of all LocusLabs buildings and associated floors for this venue, uncomment the line [self.venue listBuildings] in viewDidLoad
    NSString *locusLabsFloorId = nil;
    if ([externalFloorId isEqualToString:@"T48L3"]) locusLabsFloorId = @"lax-south-departures";
    else if ([externalFloorId isEqualToString:@"???"]) locusLabsFloorId = @"???";
    else if ([externalFloorId isEqualToString:@"???"]) locusLabsFloorId = @"???";
        
    return locusLabsFloorId;
}

- (void)mockExternalLocationData {
    
    // Position 1 (Initial - DFS Duty Free)
    NSDictionary *locationDict = @{@"FloorId": @"T48L3", @"Lat": @33.941485, @"Lon": @-118.40195};
    [self performSelector:@selector(didReceiveExternalLocationDict:) withObject:locationDict afterDelay:1.0];
    
    // Position 2 (2 secs later)
    locationDict = @{@"FloorId": @"T48L3", @"Lat": @33.941398, @"Lon": @-118.401916};
    [self performSelector:@selector(didReceiveExternalLocationDict:) withObject:locationDict afterDelay:3.0];
    
    // Position 3 (4 secs later)
    locationDict = @{@"FloorId": @"T48L3", @"Lat": @33.941283, @"Lon": @-118.401863};
    [self performSelector:@selector(didReceiveExternalLocationDict:) withObject:locationDict afterDelay:5.0];

    // Position 4 (6 secs later)
    locationDict = @{@"FloorId": @"T48L3", @"Lat": @33.941102, @"Lon": @-118.401902};
    [self performSelector:@selector(didReceiveExternalLocationDict:) withObject:locationDict afterDelay:7.0];

    // Position 5 (8 secs later - Destination - Gate 64B)
    locationDict = @{@"FloorId": @"T48L3", @"Lat": @33.940908, @"Lon": @-118.40177};
    [self performSelector:@selector(didReceiveExternalLocationDict:) withObject:locationDict afterDelay:9.0];
}

- (void)postUserPosition:(NSDictionary *)locationDict {
    
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_POSITION_SENSOR_POSITION_CHANGED
                                                        object:nil
                                                      userInfo:locationDict];
}

#pragma mark Delegates - External Positioning Data

// This is a pseudomethod to demonstrate how data may be received from an external provider and how it can be passed to our SDK
- (void)didReceiveExternalLocationDict:(NSDictionary *)externalLocationDict {

    NSString *locusLabsFloorID = [self locusLabsFloorIDForExternalFloorID:externalLocationDict[@"FloorId"]];
    if (!locusLabsFloorID) return;
    
    NSDictionary *locationDict = [self locationDictWithLat:externalLocationDict[@"Lat"] lon:externalLocationDict[@"Lon"] floorId:locusLabsFloorID heading:nil];
    [self postUserPosition:locationDict];
}

#pragma mark Delegates - LLBuilding

- (void)building:(LLBuilding *)building floorList:(NSArray *)floors {
    
    NSLog(@"Building name: %@ id: %@", building.name, building.buildingId);
    for (LLFloorInfo *floor in floors) {
        
        NSLog(@"Floor name: %@ id: %@", floor.name, floor.floorId);
    }
}

#pragma mark Delegates - LLVenue

- (void)venue:(LLVenue *)venue buildingList:(NSArray *)buildings {
    
    for (LLBuildingInfo *building in buildings) {
        
        [self.venue loadBuilding:building.buildingId];
    }
}

- (void)venue:(LLVenue *)venue buildingLoaded:(LLBuilding *)building {
    
    building.delegate = self;
    [building listFloors];
}

#pragma mark Delegates - LLVenueDatabase

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString *)venueId code:(LLDownloaderError)errorCode message:(NSString *)message {
    
    // Handle failures here
}

#pragma mark Delegates - LLMapView

- (void)mapViewDidClickBack:(LLMapView *)mapView {
    
    // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
}

- (void)mapViewReady:(LLMapView *)mapView {
  
    // Simulate receiving external location data
    [self mockExternalLocationData];
}

- (UIViewController *)presentingControllerForMapView:(LLMapView *)mapView forContext:(LLMapViewPresentationContext)context {
    
    return self;
}

@end
