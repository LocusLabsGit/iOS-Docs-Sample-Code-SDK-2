//
//  LLPersonLoaderDelegate.h
//  LocusLabsSDK
//
//  Created by Sam Ziegler on 6/3/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLPerson;
@class LLPersonLoader;

@protocol LLPersonLoaderDelegate <NSObject>

@optional

/**
 * Returns the person with the given accountSpecificId.
 */
- (void)personLoader:(LLPersonLoader *)personLoader accountSpecificId:(NSString *)accountSpecificId person:(LLPerson *)person;

/**
 * The person load failed, likely because no internet connection is available.
 */
- (void)personLoader:(LLPersonLoader *)personLoader accountSpecificId:(NSString *)accountSpecificId failure:(NSString *)reason;

@end