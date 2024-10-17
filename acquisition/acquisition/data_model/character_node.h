#pragma once

#include <acquisition/api_types/character.h>
#include <acquisition/data_model/tree_node.h>

class CharacterNode : public TreeNode
{
public:
    CharacterNode(const poe_api::Character& character, TreeNode* parent);
    ~CharacterNode() override {};
    //int columnCount() const override;
    //QVariant data(int column) const override;
private:
    void addCollection(const QString& name, const std::vector<poe_api::Item>& items);
    const poe_api::Character& m_character;
};
