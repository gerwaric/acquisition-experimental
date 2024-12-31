#include <libacq/model/rootnode.h>

#include <libacq/model/itemnode.h>

RootNode::RootNode(const QString& name, TreeNode* parent)
    : TreeNode(NodeType::Root, name, parent)
{
}
