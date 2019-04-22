//
//  cGeo.h
//  3 Gun
//
//  Created by Michael Natale on 9/4/13.
//  Copyright (c) 2013 Michael Natale. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import <MapKit/MKAnnotation.h>
#import <MapKit/MKReverseGeocoder.h>
@import CoreLocation;

@interface CursusGeo : NSObject <MKMapViewDelegate, CLLocationManagerDelegate>
{
	NSString *AirportCode;
	NSString *AirportDescription;
	NSString *CountryCode;
	NSString *Distance;
	NSString *Latitude;
	NSString *Longitude;
	NSString *StateCode;
    NSString *prevLatitude;
    NSString *prevLongitude;
    CLLocationManager *locationManager;
}

@property (strong, nonatomic) CLLocationManager *locationManager;
@property (nonatomic, strong) NSString *AirportCode;
@property (nonatomic, strong) NSString *AirportDescription;
@property (nonatomic, strong) NSString *CountryCode;
@property (nonatomic, strong) NSString *Distance;
@property (nonatomic, strong) NSString *Latitude;
@property (nonatomic, strong) NSString *Longitude;
@property (nonatomic, strong) NSString *StateCode;
@property (nonatomic, strong) NSString *prevLatitude;
@property (nonatomic, strong) NSString *prevLongitude;

-(void)GetNearestAirportByLatitiudeLongitude;
-(void)GetCurrentLatitudeLongitude;
-(NSDictionary*)kilometresBetweenPlace1:(CLLocationCoordinate2D) place1 andPlace2:(CLLocationCoordinate2D) place2;
- (void)addtarget:(id)target action:(SEL)method;
- (void)removeTarget:(id)target;

@end

