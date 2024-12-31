#pragma once

#include <libacq/poe/character.h>
#include <libacq/model/treenode.h>

class CharacterNode : public TreeNode
{
public:
    CharacterNode(const poe_api::Character& character, TreeNode* parent);
    ~CharacterNode() override {};
private:
    void addCollection(const QString& name, const std::vector<poe_api::Item>& items);
    const poe_api::Character& m_character;
};
