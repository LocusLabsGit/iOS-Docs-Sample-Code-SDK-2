//
//  GrabMapInterface.h
//  CursusLibrary
//
//  Created by Jarod Velasquez on 8/17/16.
//  Copyright © 2016 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

typedef enum
{
    GrabMapProviderLocus= 1,
    GrabMapProviderPointr
} GrabMapProvider;

@protocol GrabMapInterface <NSObject>

-(BOOL)mapsEnabled;
-(UIViewController *)getMapsVCWithAirport:(NSString *)airportCode andPoiID:(NSString *)poiID andStoreSelectedTarget:(id)target andStoreSelectedMethod:(SEL)method andSelectionEnabled:(BOOL)selectionEnabled;

@optional
-(GrabMapProvider)getMapProvider;

@end
