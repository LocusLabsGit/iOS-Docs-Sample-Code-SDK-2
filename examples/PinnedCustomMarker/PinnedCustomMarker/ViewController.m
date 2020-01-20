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
    
    // Get a reference to the POI database and set its delegate
    self.poiDatabase = self.venue.poiDatabase;
    self.poiDatabase.delegate = self;
    
    // Load the POI for Starbucks at gate 60 (to find out a POI's id, implement mapView's didTapPOI delegate method)
    [self.poiDatabase loadPOI:@"870"];
}

- (BOOL)mapView:(LLMapView *)mapView didTapMarker:(LLMarker *)marker {

    NSLog(@"Marker tapped with ID:%@", ((LLPOI*)(marker.userData)).poiId);
    // Return no to let the SDK handle the tap. If you would like to handle the tap, return YES
    return NO;
}

#pragma mark Delegates - LLPOIDatabase

- (void)poiDatabase:(LLPOIDatabase *)poiDatabase poiLoaded:(LLPOI *)poi {
    
    if ([poi.poiId isEqualToString:@"870"]) {
        
        // Add a custom marker
        LLMarker *marker = [[LLMarker alloc] init];
        marker.position = poi.position;
        marker.iconUrl = [[NSBundle mainBundle] pathForResource:@"starbucks_selected" ofType:@"svg"];
        marker.userData = poi;
        marker.map = self.mapView.map;
        
        // Keep a reference to the marker so you can remove it when necessary
        if (!self.customMarkers) self.customMarkers = [NSMutableArray array];
        [self.customMarkers addObject:marker];
    }
}

@end
