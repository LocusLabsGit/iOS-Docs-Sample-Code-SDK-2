//
// Created by Rafal Hotlos on 13/06/2018.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LLPosition;


@protocol LLNavigationDelegate <NSObject>

- (void)navigationStarted:(LLPosition *)startPoint endPoint:(LLPosition *)endPoint;

@end

@interface LLNavigation : NSObject

+ (id)initTracking;

@property (nonatomic, assign) id <LLNavigationDelegate> delegate;

@end
