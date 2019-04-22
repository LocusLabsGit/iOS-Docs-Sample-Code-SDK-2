//
//  CursusStoreSearchVW.h
//  CursusLibrary
//
//  Created by Michael Natale on 2/6/15.
//  Copyright (c) 2015 Cursus. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface CursusStoreSearchVW : UIView <UITableViewDelegate, UITableViewDataSource>
{
    NSMutableArray *arrStoresTV;
    NSMutableArray *arrStoresNonDuplicatePermHold;
    NSMutableArray *arrStoresAllPermHold;
    UITextField *txtSearch;
    UITableView *tvResults;
    UILabel *lblTitle;
    UIButton *btnClear;
}

@property (nonatomic, strong) NSMutableArray *arrStoresTV;
@property (nonatomic, strong) NSMutableArray *arrStoresNonDuplicatePermHold;
@property (nonatomic, strong) NSMutableArray *arrStoresAllPermHold;
@property (nonatomic, strong) UITextField *txtSearch;
@property (nonatomic, strong) UITableView *tvResults;
@property (nonatomic, strong) UILabel *lblTitle;
@property (nonatomic, strong) UIButton *btnClear;

-(void)addtarget:(id)target action:(SEL)method;
- (id)initWithFrame:(CGRect)frame _arrStores:(NSMutableArray*)_arrStores;

@end
