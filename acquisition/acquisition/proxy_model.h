#pragma once

#include <acquisition/api_types/item.h>
#include <acquisition/data_model/tree_model.h>

#include <QSortFilterProxyModel>

#include <unordered_map>
#include <vector>

using FilterFunction = std::function<bool(const poe_api::Item& item)>;

class ProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    ProxyModel(QObject* parent);

    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

    void setFilter(const QString& id, FilterFunction filter);
    void removeFilter(const QString& id);

private:

    std::unordered_map<QString, int> m_filter_index;

    std::vector<FilterFunction> m_filters;

};
