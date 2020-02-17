//
//  LLPersonLoader.h
//  LocusLabsSDK
//
//  Created by Sam Ziegler on 6/3/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLPersonLoaderDelegate.h"

@interface LLPersonLoader : NSObject

/**
 * The delegate for this LLPersonLoader
 */
@property (weak,nonatomic) id<LLPersonLoaderDelegate> delegate;

/**
 * Load the person with the given account specific identifier.  If the person doesn't exist, they are created.  The person is returned via the -personLoader:accountSpecificId:person: method on the delegate.
 */
- (void)load:(NSString *)accountSpecificId;

@end