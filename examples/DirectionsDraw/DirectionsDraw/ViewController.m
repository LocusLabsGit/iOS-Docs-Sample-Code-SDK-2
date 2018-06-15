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
@property (nonatomic, strong) LLFloor           *floor;
@property (nonatomic, weak)   LLMapView         *mapView;

- (LLCircle *)createCircleWithPosition:(LLPosition *)position withRadius:(NSNumber*)radius andColor:(UIColor*)color;
- (void)drawRouteWithWaypoints:(NSArray *)waypoints startFloor:(NSString *)floorID;
- (void)showSampleRoute;

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

- (LLCircle *)createCircleWithPosition:(LLPosition *)position withRadius:(NSNumber*)radius andColor:(UIColor*)color {
    
    LLCircle *circle = [LLCircle new];
    circle.position = position;
    circle.fillColor = color;
    circle.radius = radius;
    circle.map = self.mapView.map;
    
    return circle;
}

- (void)drawRouteWithWaypoints:(NSArray *)waypoints startFloor:(NSString *)floorID {
    
    LLPath *path = [[LLPath alloc] init];
    
    for (LLWaypoint *waypoint in waypoints) {
        
        [path addLatLng:waypoint.latLng];
        
        // Add a black circle at the destination
        if ([waypoint.isDestination boolValue]) {
            
            LLPosition *position = [[LLPosition alloc] initWithFloorId:floorID latLng:waypoint.latLng];
            [self createCircleWithPosition:position withRadius:@5 andColor:[UIColor blackColor]];
        }
    }
    
    // Create a new LLPolyline object and set its path
    LLPolyline *polyline = [[LLPolyline alloc] init];
    polyline.path = path;
    polyline.floorId = floorID;
    polyline.map = self.mapView.map;
}

- (void)showSampleRoute {
    
    LLLatLng *point1LatLon = [[LLLatLng alloc] initWithLat:@33.940627 lng:@-118.401892];
    LLLatLng *point2LatLon = [[LLLatLng alloc] initWithLat:@33.9410700 lng:@-118.399598];
    
    LLPosition *point1 = [[LLPosition alloc] initWithFloorId:self.floor.identifier latLng:point1LatLon];
    LLPosition *point2 = [[LLPosition alloc] initWithFloorId:self.floor.identifier latLng:point2LatLon];
    
    [self.venue navigateFrom:point1 to:point2];
}

#pragma mark Delegates - LLVenue

- (void)venue:(LLVenue *)venue navigationPath:(LLNavigationPath *)navigationPath from:(LLPosition *)startPosition toDestinations:(NSArray *)destinations  {
    
    [self drawRouteWithWaypoints:navigationPath.waypoints startFloor:startPosition.floorId];
}

#pragma mark Delegates - LLVenueDatabase

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoadFailed:(NSString *)venueId code:(LLDownloaderError)errorCode message:(NSString *)message {
    
    // Handle failures here
}

- (void)venueDatabase:(LLVenueDatabase *)venueDatabase venueLoaded:(LLVenue *)venue {
    
    self.venue = venue;
    self.venue.delegate = self;
    
    LLBuilding *building  = [self.venue loadBuilding:@"lax-south"];
    self.floor = [building loadFloor:@"lax-south-departures"];
    
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
    
    // Pan & zoom the map
    [self.mapView levelSelected:@"lax-south-departures"];
    self.mapView.mapCenter = [[LLLatLng alloc] initWithLat:@33.941384 lng:@-118.402057];
    self.mapView.mapRadius = @190.0;
    
    [self showSampleRoute];
}

@end
