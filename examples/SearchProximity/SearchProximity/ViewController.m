//
//  ViewController.m
//  SearchProximity
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, strong) LLFloor           *floor;
@property (nonatomic, weak)   LLMapView         *mapView;
@property (nonatomic, strong) LLSearch          *search;

- (void)createCircleWithPosition:(LLPosition *)position withRadius:(NSNumber*)radius andColor:(UIColor*)color;

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

#pragma mark Custom

- (void)createCircleWithPosition:(LLPosition *)position withRadius:(NSNumber*)radius andColor:(UIColor*)color {
    
    LLCircle *circle = [LLCircle new];
    circle.fillColor = color;
    circle.radius = radius;
    circle.position = position;
    circle.map = self.mapView.map;
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
    
    // Get a search instance and register as its delegate
    self.search = [self.venue search];
    self.search.delegate = self;
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
    
    // Find the nearest Starbucks to gate 60
    [self.search proximitySearchWithTerms:[NSArray arrayWithObjects:@"Starbucks",nil]
                                  floorId:@"lax-south-departures"
                                      lat:@33.94221
                                      lng:@-118.402057];
}

#pragma mark Delegates - LLSearch

- (void)proximitySearchWithTerms:(LLSearch *)search results:(LLSearchResults *)searchResults {
    
    for (LLSearchResult *searchResult in searchResults.results) {
        
        LLPosition *position = searchResult.position;
        [self createCircleWithPosition:position withRadius:@10 andColor:[UIColor redColor]];
    }
}

@end
