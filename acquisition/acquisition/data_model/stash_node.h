#pragma once

#include <acquisition/api_types/stash_tab.h>
#include <acquisition/data_model/tree_node.h>

class StashNode : public TreeNode
{
public:
    explicit StashNode(const poe_api::StashTab& stash, TreeNode* parent);
    ~StashNode() override {};
    //int columnCount() const override;
    //QVariant data(int column) const override;
private:
    const poe_api::StashTab& m_stash;
};
