#include <acquisition/float_filter.h>

FloatFilter::FloatFilter(
    SearchFilters::Filter id,
    ProxyModel& model,
    Getter<float> getter,
    QObject* parent)
    : QObject(parent)
    , m_id(id)
    , m_model(model)
    , m_getter(getter)
    , m_value(std::nan(""))
{}

void FloatFilter::setValue(float value) {
    if (!qFuzzyCompare(value, m_value)) {
        m_value = value;
        if (std::isnan(value)) {

        } else {

        };
        m_model.invalidate();
        emit valueChanged(value);
    };
};
