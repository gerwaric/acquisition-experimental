#pragma once

#include <acquisition/proxy_model.h>

template<class T>
class MinMaxFilter {
public:
    MinMaxFilter(const QString& id, ProxyModel& proxy_model, std::function<T(const ItemInfo& info)> getter)
        : m_id(id)
        , m_getter(getter)
        , m_proxy_model(proxy_model) {};

    void setMinimum(double min)
    {
        const static QString id = "MIN_" + m_id;
        updateFilter(id, min,
            [=](const ItemInfo& info) {
                return m_getter(info) >= min;
            });
    };

    void setMaximum(double max)
    {
        const static QString id = "MAX_" + m_id;
        updateFilter(id, max,
            [=](const ItemInfo& info) {
                return m_getter(info) <= max;
            });
    };

private:

    void updateFilter(const QString& id, T threshold, std::function<bool(const ItemInfo& info)> filter) {
        if (std::isnan(threshold)) {
            QLOG_DEBUG() << "Removing" << id << "filter";
            m_proxy_model.removeFilter(id);
        } else {
            QLOG_DEBUG() << "Setting" << id << "to" << threshold;
            m_proxy_model.setFilter(id, filter);
        };
    };

    const QString m_id;
    std::function<T(const ItemInfo& info)> m_getter;
    ProxyModel& m_proxy_model;
};
