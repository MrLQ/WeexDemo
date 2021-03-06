/**
 * Created by Weex.
 * Copyright (c) 2016, Alibaba, Inc. All rights reserved.
 *
 * This source code is licensed under the Apache Licence 2.0.
 * For the full copyright and license information,please view the LICENSE file in the root directory of this source tree.
 */

#ifndef __WX_DEFINE_H__
#define __WX_DEFINE_H__

#define WX_SDK_VERSION @"0.6.1"
#define WX_JS_FRAMEWORK_VERSION @"0.14.7"

#if defined(__cplusplus)
#define WX_EXTERN extern "C" __attribute__((visibility("default")))
#else
#define WX_EXTERN extern __attribute__((visibility("default")))
#endif

/*
 * Concatenate preprocessor tokens a and b without expanding macro definitions
 * (however, if invoked from a macro, macro arguments are expanded).
 */
#define WX_CONCAT(a, b)   a ## b
/*
 * Concatenate preprocessor tokens a and b after macro-expanding them.
 */
#define WX_CONCAT_WRAPPER(a, b)    WX_CONCAT(a, b)

#define WX_CONCAT_TRIPLE(a, b, c) a ## b ## c

#define WX_NSSTRING_HELPER(x) #x
#define WX_NSSTRING(x) @WX_NSSTRING_HELPER(x)

#define WX_SDK_ROOT_REF     @"_root"

#define WX_TEXT_FONT_SIZE   (32.0 * WXScreenResizeRadio())

#define WX_UPDATE_CONFIG(prefix, name, configs) \
NSString *selStr = [NSString stringWithFormat:@"%@_%@", prefix, name];\
SEL selector = NSSelectorFromString(selStr);\
Class clazz = WX_COMPONENT_CLASS(_properties[@"type"]);\
if ([clazz respondsToSelector:selector]) {\
    configs = ((NSArray *(*)(id, SEL))objc_msgSend)(clazz, selector);\
}\

#define WX_TYPE_KEYPATH(config, name, type, parts, vKey) \
type = [config[0] stringByAppendingString:@":"];\
NSString *keyPath = config.count > 1 ? config[1] : nil;\
if(keyPath){\
    parts = [keyPath componentsSeparatedByString:@"."];\
    vKey = parts.lastObject;\
parts = [parts subarrayWithRange:(NSRange){0, parts.count - 1}];\
} else {\
    vKey = name;\
}

#define RGB(r, g, b) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:1.0]
#define RGB_A(r, g, b, a) [UIColor colorWithRed:r/255.0 green:g/255.0 blue:b/255.0 alpha:a]

#define ScreenWidth  ([[UIScreen mainScreen] bounds].size.width)

#define WX_ERROR_DOMAIN @"WXErrorDomain"

#define WX_JS_ERROR_NOTIFICATION_NAME @"WXJSErrorNotification"

#define WX_INSTANCE_NOTIFICATION_UPDATE_STATE @"WXInstUpdateState"

#define WX_COMPONENT_THREAD_NAME @"com.taobao.weex.component"

#define WX_BRIDGE_THREAD_NAME @"com.taobao.weex.bridge"

/**
 *  @abstract Compared with system version of current device 
 *  
 *  @return YES if greater than or equal to the system verison, otherwise, NO.
 *
 */
#define WX_SYS_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)

/**
 *  @abstract Compared with system version of current device
 *
 *  @return YES if greater than the system verison, otherwise, NO.
 *
 */
#define WX_SYS_VERSION_GREATER_THAN(v)              ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedDescending)

/**
 *  @abstract Compared with system version of current device
 *
 *  @return YES if equal to the system verison, otherwise, NO.
 *
 */
#define WX_SYS_VERSION_EQUAL_TO(v)                  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedSame)

/**
 *  @abstract Compared with system version of current device
 *
 *  @return YES if less than the system verison, otherwise, NO.
 *
 */
#define WX_SYS_VERSION_LESS_THAN(v)                 ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] == NSOrderedAscending)

/**
 *  @abstract Compared with system version of current device
 *
 *  @return YES if less than or equal to the system verison, otherwise, NO.
 *
 */
#define WX_SYS_LESS_THAN_OR_EQUAL_TO(v)             ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedDescending)


#if __has_attribute(objc_requires_super)
    #define WX_REQUIRES_SUPER __attribute__((objc_requires_super))
#else
    #define WX_REQUIRES_SUPER
#endif

#endif
