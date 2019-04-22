#import <UIKit/UIKit.h>

@protocol CursusWSActivityViewDelegate <NSObject>

-(void)activityCancelled;

@end

@interface CursusWSActivityView : UIView

+ (CursusWSActivityView *)singleton;
- (void) showInViewWithCancelButton:(BOOL)showCancelButton;
- (void) hideInView;
- (BOOL) isVisible;

@property (nonatomic, weak) id<CursusWSActivityViewDelegate>delegate;
@property (assign) BOOL didHide;
@property (readonly) UILabel *titleLabel;
@property (strong, nonatomic) UIActivityIndicatorView *ActMonitor;
@property (weak, nonatomic) UIWindow* AppWindow;

@end
