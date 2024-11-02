#include <acquisition/float_filter.h>

FloatFilter::FloatFilter(const QString& filter_id, ProxyModel& model, QObject* parent)
    : QObject(parent)
    , m_model(model)
{}

void FloatFilter::setValue(float value) {
    if (qFuzzyCompare(value, m_value)) {
        m_value = value;
        emit valueChanged();
        m_model.invalidate();
    };
};
