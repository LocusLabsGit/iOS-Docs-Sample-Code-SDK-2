//
//  CursusPListManager.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/4/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>

#define PLIST_CURSUS_LOGIN @"cursusLogin"
#define PLIST_CURSUS_FORCE_LOGIN @"cursusForceLogin"
#define PLIST_CURSUS_DO_SSL_PINNING @"cursusDoSSLPinning"
#define PLIST_CURSUS_OAUTH @"cursusOauth"
#define PLIST_CUSTOMER_IMAGE @"customerImage"
#define PLIST_FACEBOOK_IMAGE @"facebookImage"
#define PLIST_CUSTOMER_FAVORITES @"customerFavorites"
#define PLIST_SAVED_SORT @"SavedSort"
#define PLIST_FILTER_MODAL @"filterModal"
#define PLIST_GUEST_CHECKOUT_CREDENTIALS @"dictGuestCheckoutCredentials"

@interface CursusPListManager : NSObject

+ (BOOL)writeToPlist:(NSMutableDictionary *)oDictionary sPListName:(NSString *)sPListName;
+ (NSMutableDictionary *)readFromPlist:(NSString *)sPListName;
+ (BOOL)erasePlist:(NSString *)sPListName;

@end
