//
//  GrabLoginInterface.h
//  CursusLibrary
//
//  Created by Jarod Velasquez on 7/29/16.
//  Copyright © 2016 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GrabLoginInterface <NSObject>

-(NSString *)getUserEmail;
-(BOOL)isUserLoggedIn;
-(NSString *)getPushToken;
-(NSString *)getPlayerFullName;
-(void)logout;
-(void)addLoginStatusObserver:(id)target action:(SEL)method;
-(void)removeLoginStatusObserver:(id)target;
-(void)notifyLoginStatusChange;

@end
