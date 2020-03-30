//
//  ViewController.m
//  DirectionsDraw
//
//  Created by Juan Kruger on 31/01/18.
//  Copyright © 2018 LocusLabs. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@property (nonatomic, strong) LLVenue           *venue;
@property (nonatomic, strong) LLVenueDatabase   *venueDatabase;
@property (nonatomic, weak)   LLMapView         *mapView;

- (void)showSampleRoute;

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

#pragma mark Custom

- (void)showSampleRoute {
    
    LLLatLng *point1LatLon = [[LLLatLng alloc] initWithLat:@33.940627 lng:@-118.401892];
    LLLatLng *point2LatLon = [[LLLatLng alloc] initWithLat:@33.9410700 lng:@-118.399598];
    
    // Note that you could also get LLPosition directly from an instance of LLPOI
    LLPosition *point1 = [[LLPosition alloc] initWithFloorId:self.mapView.map.floorId latLng:point1LatLon];
    LLPosition *point2 = [[LLPosition alloc] initWithFloorId:self.mapView.map.floorId latLng:point2LatLon];
    
    [self.mapView navigateFromStart:point1 end:point2];
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
    
    // Pan & zoom the map after selecting lax-south-departures
    [self.mapView levelSelected:@"lax-south-departures"];
    self.mapView.mapCenter = [[LLLatLng alloc] initWithLat:@33.941384 lng:@-118.402057];
    self.mapView.mapRadius = @190.0;
    
    [self showSampleRoute];
}

- (UIViewController *)presentingControllerForMapView:(LLMapView *)mapView forContext:(LLMapViewPresentationContext)context {
    
    return self;
}

@end
