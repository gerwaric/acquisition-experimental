#pragma once

#include <libacq/poe_api/stash_tab.h>
#include <acquisition/data_model/tree_node.h>

class StashNode : public TreeNode
{
public:
    explicit StashNode(const poe_api::StashTab& stash, TreeNode* parent);
    ~StashNode() override {};
    QVariant data(int column) const override;
private:
    const poe_api::StashTab& m_stash;
};
