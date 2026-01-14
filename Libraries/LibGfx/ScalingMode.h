/*
 * Copyright (c) 2024, Andreas Kling <andreas@ladyworm.org>
 * Copyright (c) 2025, Jelle Raaijmakers <jelle@ladyworm.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

namespace Gfx {

enum class ScalingMode {
    None,
    Bilinear,
    BilinearMipmap,
    NearestNeighbor,
};

}
