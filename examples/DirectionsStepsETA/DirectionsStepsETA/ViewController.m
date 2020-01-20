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
@property (nonatomic, weak)   LLMapView         *mapView;

- (void)getDirectionsAndETA;

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

- (void)getDirectionsAndETA {
    
    // From: Blu20 Bar, Level 3, Terminal 6, ID 1025
    // To: Gate 73, Level 3, Terminal 7, ID 551
    // Note: if you dont have poi data to get a position from, you can also construct a LLPosition directly using this method: "LLPosition *positionStart = [[LLPosition alloc] initWithFloorId: latLng:];
    [self.venue.poiDatabase loadPois:@[@"1025", @"551"] withBlock:^(NSArray *pois) {
       
        LLPOI *startPOI = nil;
        LLPOI *endPOI = nil;
        for (LLPOI *poi in pois) {
            
            if ([poi.poiId isEqualToString:@"1025"]) startPOI = poi;
            else if ([poi.poiId isEqualToString:@"551"]) endPOI = poi;
        }
        
        LLDirectionsRequest *directionsRequest = [[LLDirectionsRequest alloc] initWithStartPosition:startPOI.position endPosition:endPOI.position];
        
        [self.venue navigate:directionsRequest completion:^(LLNavigationPath *navigationPath, NSError *error) {
            
            NSLog(@"ETA:%@", navigationPath.eta);
            NSArray *wayPoints = navigationPath.waypoints;
           
            for (LLWaypoint *wayPoint in wayPoints) {
                
                NSLog(@"Waypoint:");
                NSLog(@"ETA:%@", wayPoint.eta);
                NSLog(@"Distance:%@", wayPoint.distance);
                NSLog(@"Details:%@", wayPoint.details);
                NSLog(@"Security Checkpoint?:%@", wayPoint.securityCheckpoint);
                NSLog(@"\n");
            }
        }];
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
    [self getDirectionsAndETA];
}


@end
