#pragma once

#include <libacq/data_model/item_info.h>
#include <libacq/data_model/tree_model.h>
#include <acquisition/search_filters.h>

#include <QSortFilterProxyModel>

#include <unordered_map>
#include <vector>

using FilterFunction = std::function<bool(const ItemInfo& item_info)>;

class ProxyModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    ProxyModel(QObject* parent);
    bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;
    void setFilter(SearchFilters::Filter id, FilterFunction filter);
    void removeFilter(SearchFilters::Filter id);
private:
    std::unordered_map<SearchFilters::Filter, int> m_filter_index;
    std::vector<FilterFunction> m_filters;
};
