#include <acquisition/sort_proxy.h>

#include <acquisition/data_model/item_node.h>
#include <acquisition/data_model/tree_node.h>

bool FilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    const TreeNode* node = m_model->getNode(sourceParent)->child(sourceRow);
    if (node->type() == TreeNode::NodeType::Item) {
        const ItemNode* item_node = static_cast<const ItemNode*>(node);
        const poe_api::Item& item = item_node->item();
        return filterAcceptsItem(item);
    } else {
        return true;
    };
}

bool FilterProxy::filterAcceptsItem(const poe_api::Item& item) const
{
    return true;
}
