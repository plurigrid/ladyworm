/*
 * Copyright (c) 2026, Plurigrid Contributors
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibNeural/PagePredictor.h>

namespace Neural {

ErrorOr<NonnullRefPtr<PagePredictor>> PagePredictor::create()
{
    auto predictor = adopt_ref(*new PagePredictor());
    predictor->m_operator = TRY(NeuralOperator::create());
    return predictor;
}

ErrorOr<void> PagePredictor::record_visit(URL::URL const& url)
{
    m_url_history.append(url);
    m_visit_count++;
    
    // TODO: Train the neural operator on navigation patterns
    // For now, just accumulate history
    
    return {};
}

ErrorOr<Vector<URL::URL>> PagePredictor::predict_next(size_t max_predictions) const
{
    Vector<URL::URL> predictions;
    
    // Simple heuristic: return most recent unique URLs
    // TODO: Use neural operator for actual prediction
    for (size_t i = m_url_history.size(); i > 0 && predictions.size() < max_predictions; --i) {
        auto const& url = m_url_history[i - 1];
        bool already_added = false;
        for (auto const& pred : predictions) {
            if (pred == url) {
                already_added = true;
                break;
            }
        }
        if (!already_added) {
            predictions.append(url);
        }
    }
    
    return predictions;
}

bool PagePredictor::should_prefetch(URL::URL const& url) const
{
    // TODO: Use neural operator confidence score
    // For now, check if URL has been visited before
    for (auto const& visited : m_url_history) {
        if (visited == url)
            return true;
    }
    return false;
}

}
