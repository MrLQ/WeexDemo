//
//  ViewController.m
//  WeexDemo
//
//  Created by LiQuan on 16/8/15.
//  Copyright © 2016年 LiQuan. All rights reserved.
//

#import "ViewController.h"
#import <WeexSDK/WXSDKInstance.h>
#import <WeexSDK/WeexSDK.h>
#import <SDWebImage/SDWebImageManager.h>


#pragma mark --- 自定义下载图片协议
@interface WeexImageDownloader : NSObject <WXImgLoaderProtocol>
{
    WXSDKInstance * _instance;
    
}

@end


@implementation WeexImageDownloader

- (id<WXImageOperationProtocol>)downloadImageWithURL:(NSString *)url
                                          imageFrame:(CGRect)imageFrame
                                            userInfo:(NSDictionary *)options
                                           completed:(void(^)(UIImage *image,  NSError *error, BOOL finished))completedBlock {
    return (id<WXImageOperationProtocol>)[[SDWebImageManager sharedManager] downloadImageWithURL:[NSURL URLWithString:url] options:0 progress:^(NSInteger receivedSize, NSInteger expectedSize) {
    } completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, BOOL finished, NSURL *imageURL) {
        if (completedBlock) {
            completedBlock(image, error, finished);
        }
    }];
}

@end


#pragma mark --- 自定义UI组件


@interface WeexButton : WXComponent

@property (nonatomic ,copy)NSString * title;

@property (nonatomic ,copy)UIButton * innerButton;

@end


@implementation WeexButton

- (instancetype)initWithRef:(NSString *)ref
                       type:(NSString*)type
                     styles:(nullable NSDictionary *)styles
                 attributes:(nullable NSDictionary *)attributes
                     events:(nullable NSArray *)events
               weexInstance:(WXSDKInstance *)weexInstance {
    self = [super initWithRef:ref type:type styles:styles attributes:attributes events:events weexInstance:weexInstance];
    if (self) {
        _title = [WXConvert NSString:attributes[@"title"]];
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.innerButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    self.innerButton.frame = self.view.bounds;
    [self.view addSubview:self.innerButton];
    [self.innerButton setTitle:self.title forState:UIControlStateNormal];
    [self.innerButton addTarget:self action:@selector(onButtonClick:) forControlEvents:UIControlEventTouchUpInside];
}

- (void)onButtonClick:(UIButton *)b
{

}

@end



#pragma mark  --生成界面
@interface ViewController ()
{
    WXSDKInstance * _instance;

}

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _instance = [[WXSDKInstance alloc] init];
    _instance.viewController = self;
    _instance.frame = CGRectMake(100, 100, 320, 480);
    
    __weak typeof(self) weakSelf = self;
    _instance.onCreate = ^(UIView *view) {
       [weakSelf.view addSubview:view];
    };
    
    _instance.onFailed = ^(NSError *error) {
        //process failure
    };
    
    _instance.renderFinish = ^ (UIView *view) {
        //process renderFinish
    };
    NSString *str = [NSString stringWithFormat:@"http://%@:8081/%@",@"127.0.0.1", @"q.we"];
    NSURL * url = [NSURL URLWithString:str];
    [_instance renderWithURL:url options:@{@"bundleUrl":[url absoluteString]} data:nil];
    
    //自定义协议
    [WXSDKEngine registerHandler:[WeexImageDownloader new] withProtocol:@protocol(WXImgLoaderProtocol)];
    
    
    //自定义组件
    [WXSDKEngine registerComponent:@"weex-button" withClass:[WeexButton class]];


    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
    [_instance destroyInstance];
}

@end
