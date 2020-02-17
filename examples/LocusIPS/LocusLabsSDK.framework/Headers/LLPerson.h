//
//  LLPerson.h
//  LocusLabsSDK
//
//  Created by Sam Ziegler on 6/3/15.
//  Copyright (c) 2015 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LLPerson : NSObject

/**
 * Get/Set the name of this person
 */
@property (nonatomic,strong) NSString *name;

/**
 * Get the person's account specific id.
 */
@property (readonly,nonatomic) NSString *accountSpecificId;
@property (readonly,nonatomic) NSString *personId;

@end
