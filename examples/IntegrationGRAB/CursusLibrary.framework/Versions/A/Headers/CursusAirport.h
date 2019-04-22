//
//  cAirport.h
//  RunwayGourmet
//
//  Created by Michael Natale on 10/14/13.
//  Copyright (c) 2013 Michael Natale. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface CursusAirport : NSObject
{

}

typedef void (^nearestAirportCompletionHandler)(NSDictionary *);

-(NSMutableArray*)getAllAirports;
-(NSMutableArray*)getCursusAirports;
-(NSMutableArray*)getCursusAirportsWithActiveStoreMenus;
-(NSMutableArray*)searchAllAirports:(NSString*)searchAirport;
-(NSMutableArray*)searchCursusAirports:(NSString*)searchAirport;
-(NSMutableArray*)getCursusAirportsByDistanceFromLatLon:(float)latitude longitude:(float)longitude;
//-(NSDictionary*)getNearestCursusAirport;
-(void)getNearestCursusAirport:(BOOL)bIgnoreTimestamp complete:(nearestAirportCompletionHandler)complete;
-(NSArray *)getGrabActiveAirportTerminalsWithStores;
+(NSMutableArray *)getFlightSearchAirports;
+(NSMutableArray *)getFlightSearchAirlines;


@end
