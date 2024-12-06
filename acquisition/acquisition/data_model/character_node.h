#pragma once

#include <libacq/poe_api/character.h>
#include <acquisition/data_model/tree_node.h>

class CharacterNode : public TreeNode
{
public:
    CharacterNode(const poe_api::Character& character, TreeNode* parent);
    ~CharacterNode() override {};
private:
    void addCollection(const QString& name, const std::vector<poe_api::Item>& items);
    const poe_api::Character& m_character;
};
