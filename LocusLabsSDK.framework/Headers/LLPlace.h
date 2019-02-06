//
// Created by Rafal Hotlos on 03/04/2018.
// Copyright (c) 2018 LocusLabs. All rights reserved.
//

#import <UIKit/UIKit.h>

// TODO [api] updated to enum in Swift, so use LLPlaceBehavior.POI instead of LLPlaceBehaviorPOI
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
@property (nonatomic) UIColor *selectedColor;
@property (nonatomic) UIColor *selectedIconColor;
@property (nonatomic) CGFloat cornerRadiusPercent;

@end


@interface LLPlace : NSObject

- (instancetype)initWithBehavior:(LLPlaceBehavior)behavior values:(NSArray<NSString*>*)values displayName:(NSString*)displayName andUI:(LLPlaceUI*)ui;

@property (nonatomic, readonly) LLPlaceBehavior behavior;
@property (nonatomic, readonly) NSArray<NSString*> *values;
@property (nonatomic, readonly) NSString *displayName;
@property (nonatomic, readonly) LLPlaceUI *ui;

@end
