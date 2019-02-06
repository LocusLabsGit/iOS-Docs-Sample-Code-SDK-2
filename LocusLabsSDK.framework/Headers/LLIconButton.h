//
//  LLIconButton.h
//  LocusLabsSDK
//
//  Created by Glenn Dierkes on 9/26/14.
//  Copyright (c) 2014 LocusLabs. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol LLIconButtonDelegate <NSObject>

- (void)buttonPressed:(id)sender;

@end

@interface LLIconButton : UIButton

@property (nonatomic,strong) UIImage *icon;
@property (nonatomic,strong) UIImageView *imageView;
@property (nonatomic,strong) NSString *label;
@property (nonatomic,strong) UILabel *iconLabel;
@property (nonatomic,strong) UIColor *labelColor;
@property (weak, nonatomic) id<LLIconButtonDelegate> delegate;
@property (nonatomic) NSInteger iconLabelPadding;
@property (nonatomic) BOOL labelCentered;

- (id)initWithImageTop;
- (id)initWithImageLeft;
- (id)initWithImageTopAndPad:(int)padding;
- (id)initWithImageLeftAndPad:(int)padding;
- (id)initWithImageLeftLabelTopAndPad:(int)padding;

/**
 Factory method for creating a vertically stacked icon button.
 */
+ (instancetype)topIconButtonWithPadding:(int)padding image:(UIImage*)image andLabel:(NSString*)label;

/**
 Factory method for creating a horizontal icon button.
 */
+ (instancetype)leftIconButtonWithPadding:(int)padding image:(UIImage*)image andLabel:(NSString*)label;

@end