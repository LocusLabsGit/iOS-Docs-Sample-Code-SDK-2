//
//  LLOperatingHours.h
//  LocusLabsSDK
//
//  Created by Christopher Griffith on 3/23/17.
//  Copyright © 2017 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * POI operating hours. Object of this class stores data for one day for one block of operating hours (there might be
 * multiple blocks throughout the day).
 */
@interface LLOperatingHours : NSObject

/**
 * One of "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
 */
@property (nonatomic, readonly) NSString *day;

/**
 * Start hour as integer
 */
@property (nonatomic, readonly) NSInteger startHour;
/**
 * Start minute as integer
 */
@property (nonatomic, readonly) NSInteger startMinute;
/**
 * End hour as integer
 */
@property (nonatomic, readonly) NSInteger endHour;
/**
 * End minute as integer
 */
@property (nonatomic, readonly) NSInteger endMinute;
/**
 * Whether start is am (YES) or pm (NO)
 */
@property (nonatomic, readonly) BOOL startIsAm;
/**
 * Whether end is am (YES) or pm (NO)
 */
@property (nonatomic, readonly) BOOL endIsAm;
/**
 * Start time as string, for example "8:00 AM"
 */
@property (nonatomic, readonly) NSString *startTime;
/**
 * End time as string, for example "8:00 PM"
 */
@property (nonatomic, readonly) NSString *endTime;
/**
 * Operating hours as string, for example: "8:00 AM - 8:00 PM"
 */
@property (nonatomic, readonly) NSString *hours;
/**
 * Whether POI is open 24 hours this day
 */
@property (nonatomic, readonly) BOOL isOpen24Hours;

@end
