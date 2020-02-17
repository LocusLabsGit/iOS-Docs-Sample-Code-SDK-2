//
//  LLFlightInfo.h
//  LocusLabsSDK
//
//  Created by Sam Ziegler on 11/2/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLAirline;

typedef enum LLFlightType : NSUInteger {
    LLFlightTypeArriving = 1,
    LLFlightTypeDeparting = 2
} LLFlightType;

@interface LLFlight : NSObject

@property (strong) LLAirline *airline;
@property (strong) NSString *flightCode;
@property (strong) NSString *originAirportCode;
@property (strong) NSString *originAirportName;
@property (strong) NSString *originGate;
@property (strong) NSString *destinationAirportCode;
@property (strong) NSString *destinationAirportName;
@property (strong) NSString *destinationGate;
@property (strong) NSString *baggageClaim;
@property (strong) NSDate *scheduledDepartureTime;
@property (strong) NSDate *scheduledArrivalTime;
@property (assign) LLFlightType flightType;

@end