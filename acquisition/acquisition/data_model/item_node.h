#pragma once

#include <acquisition/api_types/item.h>
#include <acquisition/data_model/tree_node.h>

class ItemNode : public TreeNode
{
public:

    enum class Column : int {
        PrettyName = 0,
        BaseType,
        Id
    };

    static constexpr int ColumnCount = 3;

    explicit ItemNode(const poe_api::Item& item, TreeNode* parent);
    ~ItemNode() override {};
    int columnCount() const override { return ColumnCount; };
    QVariant data(int column) const override;

    const poe_api::Item& item() const { return m_item; };

    enum class ItemType { None, Equipable, Stackable, Other };

private:
    const poe_api::Item& m_item;
    const ItemType m_type{ ItemType::None };
};
