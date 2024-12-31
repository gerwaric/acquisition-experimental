#pragma once

#include "proxymodel.h"

#include "searchfilters.h"

#include <libacq/poe/item.h>

#include <QObject>
#include <QQmlEngine>


template<class T>
using Getter = std::function<T(const ItemInfo& item_info)>;

using Comparator = std::function<bool(const ItemInfo& item_info)>;

class FloatFilter : public QObject {
    Q_OBJECT
    Q_PROPERTY(float value READ value WRITE setValue NOTIFY valueChanged)
    QML_ELEMENT
public:
    explicit FloatFilter(SearchFilters::Filter id, ProxyModel& model, Getter<float> getter, QObject* parent);
    inline float value() const { return m_value; };
public slots:
    void setValue(float value);
signals:
    void valueChanged(float value);
protected:
    float m_value;
    const Getter<float> m_getter;
private:
    virtual Comparator comparator() const = 0;
    const SearchFilters::Filter m_id;
    ProxyModel& m_model;
};

class MinFilter : public FloatFilter {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MinFilter(SearchFilters::Filter id, ProxyModel& model, Getter<float> getter, QObject* parent);
private:
    virtual Comparator comparator() const override;
};

class MaxFilter : public FloatFilter {
    Q_OBJECT
    QML_ELEMENT
public:
    explicit MaxFilter(SearchFilters::Filter id, ProxyModel& model, Getter<float> getter, QObject* parent);
private:
    virtual Comparator comparator() const override;
};
