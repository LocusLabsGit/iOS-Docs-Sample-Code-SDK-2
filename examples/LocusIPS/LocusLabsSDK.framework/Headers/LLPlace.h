//
// Created by Rafal Hotlos on 03/04/2018.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, LLPlaceBehavior) {
    LLPlaceBehaviorSearch,
    LLPlaceBehaviorPOI
};

@interface LLPlaceUI: NSObject

+ (instancetype)defaultUI;

@property (nonatomic) NSString *icon;
@property (nonatomic) NSString *marker;
@property (nonatomic) UIColor *normalColor;
@property (nonatomic) UIColor *normalIconColor;
@property (nonatomic) CGFloat cornerRadiusPercent;
@property (nonatomic) UIColor *selectedColor DEPRECATED_MSG_ATTRIBUTE("this attribute is not used anymore");
@property (nonatomic) UIColor *selectedIconColor DEPRECATED_MSG_ATTRIBUTE("this attribute is not used anymore");

@end


@interface LLPlace : NSObject

- (instancetype)initWithBehavior:(LLPlaceBehavior)behavior values:(NSArray<NSString*>*)values displayName:(NSString*)displayName andUI:(LLPlaceUI*)ui;

@property (nonatomic, readonly) LLPlaceBehavior behavior;
@property (nonatomic, readonly) NSArray<NSString*> *values;
@property (nonatomic, readonly) NSString *displayName;
@property (nonatomic, readonly) LLPlaceUI *ui;

@end
