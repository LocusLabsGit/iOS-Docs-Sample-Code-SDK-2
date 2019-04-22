//
//  CursusSpinnerView.h
//  CursusLibrary
//
//  Created by Michael Natale on 9/26/15.
//  Copyright © 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CursusSpinnerView : UIView
{
    UIImageView *imageSpinner;
    NSMutableArray *arrImageNames;
    NSTimer *tmrSpin1;
    NSTimer *tmrSpin2;
}

@property (nonatomic, strong) UIImageView *imageSpinner;
@property (nonatomic, strong) NSMutableArray *arrImageNames;
@property (nonatomic, strong) NSTimer *tmrSpin1;
@property (nonatomic, strong) NSTimer *tmrSpin2;

- (id)initWithFrame:(CGRect)frame imageSquareSize:(float)imageSquareSize;
-(void)startAnimation;
-(void)stopAnimation;

@end
