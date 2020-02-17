//
// Created by Rafal Hotlos on 2018-12-30.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <LocusLabsSDK/LLLogger.h>

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

#define LLLogFileInfo_ [[[NSString stringWithUTF8String:__FILE__] lastPathComponent] UTF8String]

#define LLLogError_(  FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelError   method:LLLogFileInfo_ fileInfo:nil format:FMT, ##__VA_ARGS__]
#define LLLogWarn_(   FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelWarn    method:LLLogFileInfo_ fileInfo:nil format:FMT, ##__VA_ARGS__]
#define LLLogInfo_(   FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelInfo    method:LLLogFileInfo_ fileInfo:nil format:FMT, ##__VA_ARGS__]
#define LLLogDebug_(  FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelDebug   method:LLLogFileInfo_ fileInfo:nil format:FMT, ##__VA_ARGS__]
#define LLLogVerbose_(FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelVerbose method:LLLogFileInfo_ fileInfo:nil format:FMT, ##__VA_ARGS__]
#define LLLogFixMe_(  FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelDebug   method:LLLogFileInfo_ fileInfo:nil format:FMT, ##__VA_ARGS__]

#define LLLogErrorTopic_( TOPIC, FMT, ...)   [[LLLogger defaultLogger] log:LLLogLevelError   method:nil fileInfo:nil topic:TOPIC format:FMT, ##__VA_ARGS__]
#define LLLogWarnTopic_( TOPIC, FMT, ...)    [[LLLogger defaultLogger] log:LLLogLevelWarn    method:nil fileInfo:nil topic:TOPIC format:FMT, ##__VA_ARGS__]
#define LLLogDebugTopic_(TOPIC, FMT, ...)    [[LLLogger defaultLogger] log:LLLogLevelDebug   method:nil fileInfo:nil topic:TOPIC format:FMT, ##__VA_ARGS__]
#define LLLogVerboseTopic_( TOPIC, FMT, ...) [[LLLogger defaultLogger] log:LLLogLevelVerbose method:nil fileInfo:nil topic:TOPIC format:FMT, ##__VA_ARGS__]


@interface LLLogger ()

/**
 * Whether the logs should also be appended to the logfile
 * By default it's NO
 */
@property (nonatomic) BOOL fileLoggingEnabled;

/**
 * Path of logfile where the logs are added when fileLoggingEnabled == YES
 */
@property (nonatomic, readonly) NSString *logFilePath;

- (void)log:(LLLogLevel)logLevel method:(const char*)method fileInfo:(NSString*)info message:(NSString *)message;

/**
 *  Prints out the formatted logs to the console.
 *
 *  @param logLevel The level of this log.
 *  @param fmt      The formatted string to log.
 */
- (void)log:(LLLogLevel)logLevel method:(const char*)method fileInfo:(NSString*)info format:(NSString *)fmt, ...;

/**
 * Log on a specific topic and log level
 */
- (void)log:(LLLogLevel)logLevel method:(const char*)method fileInfo:(NSString*)fileInfo topic:(LLLogTopic)topic format:(NSString *)fmt, ...;

@end
