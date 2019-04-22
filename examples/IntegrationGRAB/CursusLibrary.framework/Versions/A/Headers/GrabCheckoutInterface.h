//
//  GrabCheckoutInterface.h
//  CursusLibrary
//
//  Created by Jarod Velasquez on 7/27/16.
//  Copyright © 2016 Cursus. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol GrabCheckoutInterface <NSObject>

-(void)handleCheckout:(UINavigationController *)navController;

@end
