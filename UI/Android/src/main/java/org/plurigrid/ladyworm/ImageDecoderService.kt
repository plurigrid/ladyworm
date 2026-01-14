/**
 * Copyright (c) 2023, Andrew Kaster <akaster@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

package org.plurigrid.ladyworm

import android.os.Message

class ImageDecoderService : LadywormServiceBase("ImageDecoderService") {
    override fun handleServiceSpecificMessage(msg: Message): Boolean {
        return false
    }

    companion object {
        init {
            System.loadLibrary("imagedecoderservice")
        }
    }
}
