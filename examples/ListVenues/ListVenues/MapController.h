//
//  MapController.h
//  ListVenues
//
//  Created by Juan Kruger on 2020/04/07.
//  Copyright © 2020 LocusLabs. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <LocusLabsSDK/LocusLabsSDK.h>
NS_ASSUME_NONNULL_BEGIN

@interface MapController : UIViewController <LLVenueDatabaseDelegate, LLMapViewDelegate>

@property (nonatomic, strong) NSString *venueID;

@end

NS_ASSUME_NONNULL_END
