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
@property (nonatomic, weak)   LLMapView         *mapView;

@end

@implementation ViewController

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
    
    // Get an instance of the LLAirportDatabase, set it's mapview and register as its delegate
    self.venueDatabase = [LLVenueDatabase venueDatabaseWithMapView:self.mapView];
    self.venueDatabase.delegate = self;
    
    // Load the venue LAX async
    [self.venueDatabase loadVenueAndMap:@"lax" block:^(LLVenue *venue, LLMap *map, LLFloor *floor, LLMarker *marker) {
        
        self.mapView.map = map;
        self.floor = floor;
    }];
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
    
    // Zoom in close to the Starbucks at gate 60 on the departures level of LAX
    self.mapView.mapCenter = [[LLLatLng alloc] initWithLat:@33.94211 lng:@-118.40210];
    self.mapView.mapRadius = @50.0;
}

- (NSString *)mapView:(LLMapView *)mapView markerIconUrlForPOI:(NSString *)poiId type:(LLMapViewMarkerType)type {
    
    NSString *iconUrl = nil;
    
    // 870 is the POI ID for the Starbucks at Gate 60
    if ([poiId isEqualToString:@"870"]) {
        
        switch (type) {
                
            case LLMapViewMarkerTypeSelected:
                iconUrl = [[NSBundle mainBundle] pathForResource:@"starbucks_selected.svg" ofType:nil];
                break;
                
            case LLMapViewMarkerTypeUnselected:
                iconUrl = [[NSBundle mainBundle] pathForResource:@"starbucks_unselected.svg" ofType:nil];
                break;
        }
    }
    
    return iconUrl;
}

@end
