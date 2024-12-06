#include <libacq/data_model/root_node.h>

#include <libacq/data_model/item_node.h>

RootNode::RootNode(const QString& name, TreeNode* parent)
    : TreeNode(NodeType::Root, name, parent)
{
}
