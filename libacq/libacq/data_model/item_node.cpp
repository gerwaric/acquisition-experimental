#include <libacq/data_model/item_node.h>

ItemNode::ItemNode(const poe_api::Item& item, TreeNode* parent)
    : TreeNode(NodeType::Item, item.baseType, parent)
    , m_item(item)
    , m_item_info(std::make_unique<ItemInfo>(item))
{
    if (item.socketedItems) {
        addChildren<ItemNode>(item.socketedItems.value());
    };
}

QVariant ItemNode::data(int column) const
{
    switch (column) {
    case static_cast<int>(Column::PrettyName):
        return (m_item.name.isEmpty()) ? m_item.typeLine : m_item.name + " " + m_item.typeLine;
    case static_cast<int>(Column::BaseType):
        return m_item.baseType;
    case static_cast<int>(Column::Id):
        return m_item.id.value_or("");
    default:
        return QVariant();
    }
}
