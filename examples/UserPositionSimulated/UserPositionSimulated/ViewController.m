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
@property (nonatomic, weak)   LLMapView         *mapView;

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
    
    // Get an instance of LLVenueDatabase, set it's mapview and register as its delegate
    self.venueDatabase = [LLVenueDatabase venueDatabaseWithMapView:self.mapView];
    self.venueDatabase.delegate = self;
    
    // Load the venue LAX async
    [self.venueDatabase loadVenueAndMap:@"lax" block:^(LLVenue *venue, LLMap *map, LLFloor *floor, LLMarker *marker) {
        
        self.mapView.map = map;
        self.venue = venue;
        self.mapView.positioningEnabled = YES;
    }];
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

#pragma mark Delegates - LLVenueDatabase

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString *)venueId code:(LLDownloaderError)errorCode message:(NSString *)message {
    
    // Handle failures here
}

#pragma mark Delegates - LLMapView

- (void)mapViewDidClickBack:(LLMapView *)mapView {
    
    // The user tapped the "Cancel" button while the map was loading. Dismiss the app or take other appropriate action here
}

- (void)mapViewReady:(LLMapView *)mapView {

    // Set the navigation source to internal & send timed navigation points
    [[NSNotificationCenter defaultCenter] postNotificationName:NOTIFICATION_SET_POSITIONING_SENSOR_ALGORITHM
                                                        object:nil
                                                      userInfo:@{@"positioningSensorAlgorithm":@(LLPositioningSensorAlgorithmExternal)}];
    
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

@end
