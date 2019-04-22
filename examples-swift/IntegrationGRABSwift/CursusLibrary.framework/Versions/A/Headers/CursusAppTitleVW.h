//
//  CursusAppTitleVW.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/5/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CursusAppTitleVW : UIView
{
    UILabel *lblTitleBottom;
    UILabel *lblTitleTop;
    UIButton *btnLocation;
    UIImageView *imgGraySeperatorTop;
    UIImageView *imgGraySeperatorBottom;
}

@property (nonatomic, strong) UILabel *lblTitleBottom;
@property (nonatomic, strong) UILabel *lblTitleTop;
@property (nonatomic, strong) UIButton *btnLocation;
@property (nonatomic, strong) UIImageView *imgGraySeperatorTop;
@property (nonatomic, strong) UIImageView *imgGraySeperatorBottom;

-(NSString*)showTitleDisplay:(BOOL)bShowDetailedLocation;
- (id)initWithFrame:(CGRect)frame  bShowLocationButton:(BOOL)bShowLocationButton bShowDetailedLocation:(BOOL)bShowDetailedLocation;
-(void)resizeToFit;

@end

