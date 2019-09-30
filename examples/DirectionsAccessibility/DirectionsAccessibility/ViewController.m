//
//  ViewController.m
//  DirectionsAccessibility
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, weak)   LLMapView         *mapView;

- (void)requestWheelchairDirectionsAndETAProgrammatically;

@end

@implementation ViewController

#pragma mark Lifecycle

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    // Initialize the LocusLabs SDK with the accountId provided by LocusLabs
    [LLLocusLabs setup].accountId = @"A11F4Y6SZRXH4X"; //base
    
    // Set accessibility preference for the user (this affects the preference toggle in the directions interface)
    [LLUserPreferences shared].preferWheelchairAccessibleNavigation = YES;
    
    // Create a new LLMapView, register as its delegate and add it as a subview
    LLMapView *mapView = [[LLMapView alloc] initWithFrame:self.view.bounds];
    mapView.autoresizingMask = (UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight);
    mapView.delegate = self;
    [self.view addSubview:mapView];
    
    self.mapView = mapView;
    
    // Get an instance of LLVenueDatabase, set it's mapview and register as its delegate
    self.venueDatabase = [LLVenueDatabase venueDatabaseWithMapView:self.mapView];
    self.venueDatabase.delegate = self;
    
    // Load the venue LAX async
    [self.venueDatabase loadVenueAndMap:@"lax" block:^(LLVenue *venue, LLMap *map, LLFloor *floor, LLMarker *marker) {
        
        self.venue = venue;
        
        [self requestWheelchairDirectionsAndETAProgrammatically];
    }];
}

- (void)requestWheelchairDirectionsAndETAProgrammatically {
    
    LLLatLng *point1LatLon = [[LLLatLng alloc] initWithLat:@33.940627 lng:@-118.401892];
    LLLatLng *point2LatLon = [[LLLatLng alloc] initWithLat:@33.9410700 lng:@-118.399598];
    
    // Note that you could also get LLPosition directly from an instance of LLPOI
    LLPosition *positionStart = [[LLPosition alloc] initWithFloorId:@"lax-south-departures" latLng:point1LatLon];
    LLPosition *positionEnd = [[LLPosition alloc] initWithFloorId:@"lax-south-departures" latLng:point2LatLon];
    
    LLDirectionsRequest *directionsRequest = [[LLDirectionsRequest alloc] initWithStartPosition:positionStart endPosition:positionEnd];
    
    // Specify wheelchair accessible directions only
    directionsRequest.forceWheelchairAccessibleRoute = YES;
    
    // Get step by step directions
    [self.venue navigate:directionsRequest completion:^(LLNavigationPath *navigationPath, NSError *error) {
        
        if (error) NSLog(@"navigation path unavailable: %@", [error localizedDescription]);
        else NSLog(@"navigation path:%@", navigationPath);
    }];
    
    // Get an eta for the route
    [self.venue timeEstimate:directionsRequest completion:^(NSNumber *timeEstimate, NSError *error) {
        
        if (error) NSLog(@"time estimate unavailable: %@", [error localizedDescription]);
        else NSLog(@"time estimate: %@", timeEstimate);
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
    
    // The map is ready to be used in calls e.g. zooming, showing poi, etc.
}

@end
