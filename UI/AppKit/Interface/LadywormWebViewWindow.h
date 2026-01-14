/*
 * Copyright (c) 2024, Tim Flynn <trflynn89@ladyworm.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#import <Cocoa/Cocoa.h>

@class LadywormWebView;

@interface LadywormWebViewWindow : NSWindow

- (instancetype)initWithWebView:(LadywormWebView*)web_view
                     windowRect:(NSRect)window_rect;

@property (nonatomic, strong) LadywormWebView* web_view;

@end
