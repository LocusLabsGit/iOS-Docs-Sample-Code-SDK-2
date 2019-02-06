/*
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#import <Foundation/Foundation.h>


typedef NS_ENUM(NSInteger, LLLogLevel) {
    LLLogLevelUnknown = -1,
    LLLogLevelNone = 0,
    LLLogLevelError = 1,
    LLLogLevelWarn = 2,
    LLLogLevelInfo = 3,
    LLLogLevelDebug = 4,
    LLLogLevelVerbose = 5,
    LLLogLevelTrace = 5
};

typedef NS_ENUM(NSInteger, LLLogTopic) {
    LLLogTopicAllTopics = -1,
    LLLogTopicNoSpecificTopic = 1 << 0,
    LLLogTopicPositioning = 1 << 1,
    LLLogTopicLoading = 1 << 2
};

/**
 *  LLLogger is an utility class that handles logging to the console.
 *  You can specify the log level to control how verbose the output will be.
 */
@interface LLLogger : NSObject

/**
*  The log level setting. The default is LLLogLevelNone.
*/
@property (atomic, assign) LLLogLevel logLevel;

/**
 *  The topics to log. Default is LLLogTopicAllTopics; OR together topics if you don't want them all:
 *
 *      LLLogTopicPositioning | LLLogTopicXYZ
 */
@property (atomic, assign) LLLogTopic logTopics;

/**
 *  Returns the shared logger object.
 *
 *  @return The shared logger object.
 */
+ (instancetype)defaultLogger;

@end
