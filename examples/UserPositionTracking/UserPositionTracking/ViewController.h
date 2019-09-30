//
//  ViewController.h
//  UserPositionTracking
//
//  Created by Juan Kruger on 05/02/18.
//  Copyright © 2019 LocusLabs. All rights reserved.
//

#import <UIKit/UIKit.h>

#import <LocusLabsSDK/LocusLabsSDK.h>

@interface ViewController : UIViewController <LLVenueDatabaseDelegate, LLMapViewDelegate, LLVenueDelegate, LLBuildingDelegate, LLPositionManagerDelegate>


@end

