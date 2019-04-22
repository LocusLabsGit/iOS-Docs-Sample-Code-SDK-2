//
//  GrabClientInterface.h
//  TestGrabFramework
//
//  Created by Jarod Velasquez on 8/30/16.
//  Copyright © 2016 Jarod Velasquez. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

typedef void (^getGrabActiveAirportsCompletionHandler)(NSDictionary *);
typedef void (^getGrabActiveAirportsTerminalsCompletionHandler)(NSArray *);
typedef void (^grabSystemCheckCompletionHandler)(BOOL);

@protocol GrabClientInterface <NSObject>

+(void)grabSystemCheck:(NSString *)customerCode withCompletion:(grabSystemCheckCompletionHandler)completion;
+(void)grabSystemCheck:(NSString *)customerCode andTimeout:(NSInteger)timeout withCompletion:(grabSystemCheckCompletionHandler)completion;
+(void)initializeGrabSDKwithCustomerCode:(NSString *)customerCode andDictStyle:(NSMutableDictionary*)dictGrabStyle;
+(UIViewController *)getGrabShoppingVCWithAirportCode:(NSString *)airportCode;
+(UIViewController *)getGrabShoppingVCWithAirportCode:(NSString *)airportCode andTerminalName:(NSString *)terminalName;
+(UIViewController *)getGrabShoppingVCWithAirportCode:(NSString *)airportCode andTerminalName:(NSString *)terminalName andGate:(NSString*)gate;
+(UIViewController *)getStoreShoppingWithAirportCode:(NSString *)airportCode andPOIID:(NSString *)POIID;
+(UIViewController *)getStoreShoppingWithAirportCode:(NSString *)airportCode andPointrPOIID:(NSString *)PointrPOIID;
+(UIViewController *)getStoreShoppingWithAirportCode:(NSString *)airportCode andWaypointID:(NSString *)waypointID;
+(void)getGrabActiveStoresByAirport:(NSString *)airportCode withCompletionHandler:(getGrabActiveAirportsCompletionHandler)completion;
+(void)getGrabActiveStoresByAirport:(NSString *)airportCode bLocusLabsStoresOnly:(BOOL)bLocusLabsStoresOnly withCompletionHandler:(getGrabActiveAirportsCompletionHandler)completion;
+(void)getGrabActiveAirports:(getGrabActiveAirportsCompletionHandler)completion;
+(void)getGrabActiveAirportTerminalsWithStores:(getGrabActiveAirportsTerminalsCompletionHandler)completion;
+(NSArray *)getGrabActiveAirportTerminalsWithStoresFromCache;

@end
