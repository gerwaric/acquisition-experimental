#include <acquisition/proxy_model.h>

#include <acquisition/data_model/item_node.h>
#include <acquisition/data_model/tree_node.h>

#include <QsLog/QsLog.h>

ProxyModel::ProxyModel(QObject* parent) : QSortFilterProxyModel(parent)
{
}

bool ProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    if (!sourceParent.isValid()) {
        return true;
    };

    // WARNINGS: this assumes the source model contains TreeNode objects
    const TreeNode* parent = static_cast<TreeNode*>(sourceParent.internalPointer());
    if (!parent) {
        QLOG_ERROR() << "ProxyModel::filterAcceptsRow() source parent internal pointer is null";
        return true;
    }

    const TreeNode* node = parent->child(sourceRow);
    if (!node) {
        QLOG_ERROR() << "ProxyModel::filterAcceptsRow() node pointer is null";
        return true;
    };

    if (node->type() == TreeNode::NodeType::Item) {
        const ItemNode* item_node = static_cast<const ItemNode*>(node);
        const poe_api::Item& item = item_node->item();
        for (const auto& filter : m_filters) {
            if (!filter(item)) {
                return false;
            };
        };
    };
    return true;
}

void ProxyModel::setFilter(const QString& id, FilterFunction filter)
{
    if (m_filter_index.count(id) == 0) {
        m_filters.push_back(filter);
        m_filter_index[id] = m_filters.size() - 1;
    } else {
        const int i = m_filter_index[id];
        m_filters[i] = filter;
    };
}

void ProxyModel::removeFilter(const QString& id)
{
    if (m_filter_index.count(id) == 0) {
        QLOG_ERROR() << "ProxyModel::removeFilter() filter does not exist:" << id;
        return;
    };
    const int i = m_filter_index[id];
    m_filters.erase(m_filters.begin() + i);
    m_filter_index.erase(id);
}
