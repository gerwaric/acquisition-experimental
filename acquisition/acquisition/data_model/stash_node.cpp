#include <acquisition/data_model/stash_node.h>

#include <acquisition/data_model/item_node.h>

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
