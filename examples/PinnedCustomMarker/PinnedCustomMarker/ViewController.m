//
//  ViewController.m
//  ShowFullscreenMap
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, strong) LLFloor           *floor;
@property (nonatomic, strong) NSMutableArray    *customMarkers;
@property (nonatomic, weak)   LLMapView         *mapView;
@property (nonatomic, strong) LLPOIDatabase     *poiDatabase;

@end

@implementation ViewController

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
}

#pragma mark Delegates - LLMapView

- (void)mapViewDidClickBack:(LLMapView *)mapView {
    
    // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
}

- (void)mapViewReady:(LLMapView *)mapView {
    
    // Get a reference to the POI database and set its delegate
    self.poiDatabase = self.venue.poiDatabase;
    self.poiDatabase.delegate = self;
    
    // Load the POI for Starbucks at gate 60 (to find out a POI's id, implement mapView's didTapPOI delegate method)
    [self.poiDatabase loadPOI:@"870"];
}

#pragma mark Delegates - LLPOIDatabase

- (void)poiDatabase:(LLPOIDatabase *)poiDatabase poiLoaded:(LLPOI *)poi {
    
    if ([poi.poiId isEqualToString:@"870"]) {
        
        // Add a custom marker
        LLMarker *marker = [[LLMarker alloc] init];
        marker.position = poi.position;
        marker.iconUrl = [[NSBundle mainBundle] pathForResource:@"starbucks_selected.svg" ofType:nil];
        marker.userData = poi;
        marker.map = self.mapView.map;
        
        // Keep a reference to the marker so you can remove it when necessary
        if (!self.customMarkers) self.customMarkers = [NSMutableArray array];
        [self.customMarkers addObject:marker];
    }
}

@end
