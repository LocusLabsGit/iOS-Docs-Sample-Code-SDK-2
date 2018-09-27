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

#define LLLogFileInfo [NSString stringWithFormat:@"%@:%d", [[NSString stringWithUTF8String:__FILE__] lastPathComponent], __LINE__]

#define LLLogError(              FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelError   method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo             format:FMT, ##__VA_ARGS__]
#define LLLogWarn(               FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelWarn    method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo             format:FMT, ##__VA_ARGS__]
#define LLLogInfo(               FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelInfo    method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo             format:FMT, ##__VA_ARGS__]
#define LLLogDebug(              FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelDebug   method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo             format:FMT, ##__VA_ARGS__]
#define LLLogVerbose(            FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelVerbose method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo             format:FMT, ##__VA_ARGS__]
                                                                                                                                                      
#define LLLogFixMe(              FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelDebug   method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo             format:FMT, ##__VA_ARGS__]
                                                                                                                                                      
#define LLLogErrorTopic(  TOPIC, FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelError   method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo topic:TOPIC format:FMT, ##__VA_ARGS__]
#define LLLogWarnTopic(   TOPIC, FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelWarn    method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo topic:TOPIC format:FMT, ##__VA_ARGS__]
#define LLLogInfoTopic(   TOPIC, FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelInfo    method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo topic:TOPIC format:FMT, ##__VA_ARGS__]
#define LLLogDebugTopic(  TOPIC, FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelDebug   method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo topic:TOPIC format:FMT, ##__VA_ARGS__]
#define LLLogVerboseTopic(TOPIC, FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelVerbose method:__PRETTY_FUNCTION__ fileInfo:LLLogFileInfo topic:TOPIC format:FMT, ##__VA_ARGS__]

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
    LLLogTopicAllTopics       = -1,
    LLLogTopicNoSpecificTopic = 1 << 0,
    LLLogTopicPositioning     = 1 << 1,
    LLLogTopicLoading         = 1 << 2
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

/**
 * Whether the logs should also be appended to the logfile
 * By default it's NO
 */
@property (nonatomic) BOOL fileLoggingEnabled;

/**
 * Path of logfile where the logs are added when fileLoggingEnabled == YES
 */
@property (nonatomic, readonly) NSString *logFilePath;

/**
 *  Prints out the formatted logs to the console.
 *
 *  @param logLevel The level of this log.
 *  @param fmt      The formatted string to log.
 */
- (void)log:(LLLogLevel)logLevel method:(const char*)method fileInfo:(NSString*)info format:(NSString *)fmt, ...;

/*
 * Log on a specific topic and log level
 */
- (void)log:(LLLogLevel)logLevel method:(const char*)method fileInfo:(NSString*)info topic:(LLLogTopic)topic format:(NSString *)fmt, ...;


@end
