#pragma once

#include <libacq/poe_api/stash_tab.h>
#include <acquisition/data_model/tree_node.h>

class RootNode : public TreeNode
{
public:
    explicit RootNode(const QString& name, TreeNode* parent = nullptr);
    ~RootNode() override {};
    //int columnCount() const override;
    //QVariant data(int column) const override;
};
