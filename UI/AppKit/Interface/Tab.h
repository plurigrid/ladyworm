/*
 * Copyright (c) 2023-2024, Tim Flynn <trflynn89@ladyworm.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Types.h>

#import <Cocoa/Cocoa.h>
#import <Interface/LadywormWebViewWindow.h>

@class LadywormWebView;

@interface Tab : LadywormWebViewWindow

- (instancetype)init;
- (instancetype)initAsChild:(Tab*)parent
                  pageIndex:(u64)page_index;

@end
