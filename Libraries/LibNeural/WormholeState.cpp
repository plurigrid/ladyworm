/*
 * Copyright (c) 2026, Plurigrid Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibNeural/WormholeState.h>

namespace Neural {

WormholeState& WormholeState::the()
{
    static WormholeState s_instance;
    return s_instance;
}

ErrorOr<void> WormholeState::share_state(String const& key, Vector<float> const& state)
{
    m_shared_states.set(key, state);
    return {};
}

ErrorOr<Vector<float>> WormholeState::get_shared_state(String const& key) const
{
    auto it = m_shared_states.find(key);
    if (it == m_shared_states.end())
        return Vector<float> {};
    return it->value;
}

bool WormholeState::has_shared_state(String const& key) const
{
    return m_shared_states.contains(key);
}

ErrorOr<Vector<float>> WormholeState::merge_states(Vector<String> const& keys) const
{
    Vector<float> merged;
    size_t count = 0;
    
    for (auto const& key : keys) {
        auto it = m_shared_states.find(key);
        if (it == m_shared_states.end())
            continue;
            
        auto const& state = it->value;
        if (merged.is_empty()) {
            merged = state;
        } else {
            // Average the states
            for (size_t i = 0; i < merged.size() && i < state.size(); ++i) {
                merged[i] = (merged[i] * count + state[i]) / (count + 1);
            }
        }
        count++;
    }
    
    return merged;
}

void WormholeState::clear_state(String const& key)
{
    m_shared_states.remove(key);
}

void WormholeState::clear_all()
{
    m_shared_states.clear();
}

}
