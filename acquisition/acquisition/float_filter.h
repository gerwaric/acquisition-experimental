#pragma once

#include <acquisition/proxy_model.h>

#include <acquisition/api_types/item.h>
#include <acquisition/search_filters.h>

#include <QObject>

template<class T>
using Getter = std::function<T(const ItemInfo& item_info)>;

class FloatFilter : public QObject {
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit FloatFilter(
        SearchFilters::Filter id,
        ProxyModel& model,
        Getter<float> getter,
        QObject* parent);
    inline float value() const { return m_value; };
public slots:
    void setValue(float value);
signals:
    void valueChanged(float value);
private:
    const SearchFilters::Filter m_id;
    ProxyModel& m_model;
    Getter<float> m_getter;
    float m_value;
};
