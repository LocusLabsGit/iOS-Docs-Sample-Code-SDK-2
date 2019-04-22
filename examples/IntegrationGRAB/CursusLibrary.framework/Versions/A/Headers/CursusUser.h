//
//  cPlayer.h
//  SudokuRace
//
//  Created by Michael Natale on 10/26/13.
//  Copyright (c) 2013 mobileTrek. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GrabLoginInterface.h"

static NSString * kLOGIN_STATUS_CHANGE_NOTIFICATION = @"loginStatusChangeNotification";

@interface CursusUser : NSObject

+(NSString*)getPlayerFirstName;
+(NSString*)getPlayerLastName;
+(NSString*)getPlayerFullName;
+(NSString*)getPlayerEmail;
+(NSString*)getAPNSDeviceToken;
+(BOOL)isPlayerLoggedIn;
+(BOOL)isFirstTimeAppStart;
+(UIImage *) getImageFromURL:(NSString *)fileURL;
+(void)LogUserOut;
+(void)addLoginStatusObserver:(id)target action:(SEL)method;
+(void)removeLoginStatusObserver:(id)target;
+(void)notifyLoginStatusChange;

@end
