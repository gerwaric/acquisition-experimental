#pragma once

#include <libacq/poe/stashtab.h>
#include <libacq/model/treenode.h>

class RootNode : public TreeNode
{
public:
    explicit RootNode(const QString& name, TreeNode* parent = nullptr);
    ~RootNode() override {};
    //int columnCount() const override;
    //QVariant data(int column) const override;
};
