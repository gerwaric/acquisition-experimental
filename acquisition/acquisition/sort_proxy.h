#pragma once

#include <acquisition/api_types/item.h>
#include <acquisition/data_model/tree_model.h>

#include <QSortFilterProxyModel>

#include <vector>

class ItemFilter {
public:
    virtual bool accepts(const poe_api::Item& item) const;
};

class FilterProxy : public QSortFilterProxyModel {
    Q_OBJECT
public:
    FilterProxy(QObject* parent) : QSortFilterProxyModel(parent) {};
    ~FilterProxy() {};

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

private:

    bool filterAcceptsItem(const poe_api::Item& item) const;

    TreeModel* m_model;
    std::vector<ItemFilter> m_filters;
};
