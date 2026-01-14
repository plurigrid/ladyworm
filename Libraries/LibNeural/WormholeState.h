/*
 * Copyright (c) 2026, Plurigrid Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/HashMap.h>
#include <AK/RefCounted.h>
#include <AK/String.h>
#include <AK/Vector.h>
#include <LibNeural/Forward.h>

namespace Neural {

// WormholeState: Cross-tab neural state sharing
// Enables tabs to share learned patterns and predictions
class WormholeState : public RefCounted<WormholeState> {
public:
    static WormholeState& the();
    
    // State sharing between tabs
    ErrorOr<void> share_state(String const& key, Vector<float> const& state);
    ErrorOr<Vector<float>> get_shared_state(String const& key) const;
    bool has_shared_state(String const& key) const;
    
    // Merge states from multiple tabs
    ErrorOr<Vector<float>> merge_states(Vector<String> const& keys) const;
    
    // Cleanup
    void clear_state(String const& key);
    void clear_all();

private:
    WormholeState() = default;
    
    HashMap<String, Vector<float>> m_shared_states;
};

}
