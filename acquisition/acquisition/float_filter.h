#pragma once

#include <acquisition/proxy_model.h>

#include <acquisition/api_types/item.h>

#include <QObject>

class FloatFilter : public QObject {
    Q_OBJECT
    Q_PROPERTY(value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit FloatFilter(
        const QString& filter_id,
        std::function<float(const poe_api::Item& item)> getter,
        ProxyModel& model,
        QObject* parent);
    float value() const { return m_value; };
    void setValue(float value);
signals:
    void valueChanged();
private:
    float m_value;
    std::function<float(const poe_api::Item& item)> m_getter;
    ProxyModel& m_model;
};
