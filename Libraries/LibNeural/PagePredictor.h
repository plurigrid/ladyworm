/*
 * Copyright (c) 2026, Plurigrid Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/RefCounted.h>
#include <AK/String.h>
#include <AK/URL.h>
#include <AK/Vector.h>
#include <LibNeural/NeuralOperator.h>

namespace Neural {

// PagePredictor: Predicts likely next page loads for prefetching
// Uses NeuralOperator to learn user navigation patterns
class PagePredictor : public RefCounted<PagePredictor> {
public:
    static ErrorOr<NonnullRefPtr<PagePredictor>> create();
    
    // Record a page visit
    ErrorOr<void> record_visit(URL::URL const& url);
    
    // Get predicted next URLs (sorted by probability)
    ErrorOr<Vector<URL::URL>> predict_next(size_t max_predictions = 5) const;
    
    // Prefetch hint for the browser
    bool should_prefetch(URL::URL const& url) const;
    
    // Stats
    size_t total_visits() const { return m_visit_count; }
    size_t unique_urls() const { return m_url_history.size(); }

private:
    PagePredictor() = default;
    
    NonnullRefPtr<NeuralOperator> m_operator;
    Vector<URL::URL> m_url_history;
    size_t m_visit_count { 0 };
    float m_prefetch_threshold { 0.7f };
};

}
