#include <libacq/model/characternode.h>

#include <libacq/model/itemnode.h>
#include <libacq/model/rootnode.h>

#include <QsLog/QsLog.h>

CharacterNode::CharacterNode(const poe_api::Character& character, TreeNode* parent)
    : TreeNode(NodeType::Character, character.name, parent)
    , m_character(character)
{
    QLOG_TRACE() << "Creating CharacterNode for" << character.name << "under" << parent->name();

    if (character.equipment) {
        addCollection("Equipment", character.equipment.value());
    };
    if (character.inventory) {
        addCollection("Inventory", character.inventory.value());
    };
    if (character.rucksack) {
        addCollection("Rucksack", character.rucksack.value());
    };
    if (character.jewels) {
        addCollection("Jewels", character.jewels.value());
    };
}

void CharacterNode::addCollection(const QString& name, const std::vector<poe_api::Item>& items)
{
    addChild<RootNode>(name).addChildren<ItemNode>(items);
}
