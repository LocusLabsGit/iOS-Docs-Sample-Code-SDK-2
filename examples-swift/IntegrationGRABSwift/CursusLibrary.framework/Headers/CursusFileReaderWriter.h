//
//  cFileReaderWriter.h
//  ContinentalMasterXCode
//
//  Created by Michael Natale on 5/21/10.
//  Copyright 2010 Continental Airlines. All rights reserved.
//

#import <Foundation/Foundation.h>

#define APNS_TOKEN_FILE_PATH @"apnsdevicetoken.txt"

@interface CursusFileReaderWriter : NSObject {

}

+(void) writeTextToTextFile:(NSString *)fileName textToWrite:(NSString *)textToWrite;
+(NSString *) readTextToDisplay: (NSString *)fileName ;

@end
