#include <libacq/data_model/stash_node.h>

#include <libacq/data_model/item_node.h>

StashNode::StashNode(const poe_api::StashTab& stash, TreeNode* parent)
    : TreeNode(NodeType::Stash, stash.name, parent)
    , m_stash(stash)
{
    QLOG_TRACE() << "Creating StashNode for" << stash.name << "under" << parent->name();

    if (stash.children) {
        addChildren<StashNode>(stash.children.value());
    };
    if (stash.items) {
        addChildren<ItemNode>(stash.items.value());
    };
}

QVariant StashNode::data(int column) const
{
    if (column > 0) {
        return "";
    } else if (m_stash.index) {
        return QString("#%1, %2").arg(QString::number(m_stash.index.value()), m_stash.name);
    } else {
        return m_stash.name;
    };
}
