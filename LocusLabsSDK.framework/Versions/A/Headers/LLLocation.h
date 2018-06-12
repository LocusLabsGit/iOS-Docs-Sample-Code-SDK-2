//
//  LLLocation.h
//  LocusLabsSDK
//
//  Created by Glenn Dierkes on 11/30/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//


@interface LLLocation : NSObject

/**
 *  @return the id of the location
 */
@property (readonly) NSString *identifier;

/**
 *  @return the name of the location
 */
@property (readonly) NSString *name;

/**
 *  @return the details of the location
 */
@property (readonly) NSString *details;

/**
 *  @return the address of the location
 */
@property (readonly) NSString *address;

/**
 *  @return the website of the location
 */
@property (readonly) NSString *website;

/**
 *  @return the hours of the location
 */
@property (readonly) NSString *hours;

/**
 *  @return the phone of the location
 */
@property (readonly) NSString *phone;

/**
 *  @return the category of the location
 */
@property (readonly) NSString *category;

/**
 *  @return the keywords of the location
 */
@property (readonly) NSArray *keywords;

/**
 *  @return the access of the location
 */
@property (readonly) NSString *access;

/**
 *  @return the attribiutes of the location
 */
@property (readonly) NSDictionary *attributes;

@end