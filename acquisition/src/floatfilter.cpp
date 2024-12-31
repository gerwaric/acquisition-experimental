#include "floatfilter.h"

FloatFilter::FloatFilter(SearchFilters::Filter id, ProxyModel& model, Getter<float> getter, QObject* parent)
    : QObject(parent)
    , m_value(std::nan(""))
    , m_getter(getter)
    , m_id(id)
    , m_model(model)
{}

void FloatFilter::setValue(float value) {
    if (!qFuzzyCompare(value, m_value)) {
        m_value = value;
        if (std::isnan(value)) {
            m_model.removeFilter(m_id);
        } else {
            m_model.setFilter(m_id, comparator());
        };
        m_model.invalidate();
        emit valueChanged(value);
    };
}

MinFilter::MinFilter(SearchFilters::Filter id, ProxyModel& model, Getter<float> getter, QObject* parent)
    : FloatFilter(id, model, getter, parent)
{}

Comparator MinFilter::comparator() const
{
    return [=](const ItemInfo& item_info) {
        return m_getter(item_info) >= m_value;
    };
}

MaxFilter::MaxFilter(SearchFilters::Filter id, ProxyModel& model, Getter<float> getter, QObject* parent)
    : FloatFilter(id, model, getter, parent)
{}

Comparator MaxFilter::comparator() const
{
    return [=](const ItemInfo& item_info) {
        return m_getter(item_info) <= m_value;
    };
}
