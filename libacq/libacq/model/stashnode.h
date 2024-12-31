#pragma once

#include <libacq/poe/stashtab.h>
#include <libacq/model/treenode.h>

class StashNode : public TreeNode
{
public:
    explicit StashNode(const poe_api::StashTab& stash, TreeNode* parent);
    ~StashNode() override {};
    QVariant data(int column) const override;
private:
    const poe_api::StashTab& m_stash;
};
