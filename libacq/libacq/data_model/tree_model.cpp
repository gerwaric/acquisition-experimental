#include <libacq/data_model/tree_model.h>

#include <libacq/data_model/character_node.h>
#include <libacq/data_model/item_node.h>
#include <libacq/data_model/stash_node.h>

TreeModel::TreeModel(QObject* parent)
    : QAbstractItemModel(parent)
    , m_root("Root")
    , m_character_root(m_root.addChild<RootNode>("Characters"))
    , m_stash_root(m_root.addChild<RootNode>("Stash Tabs")) {}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    const TreeNode* parent_node = getNode(parent);
    if (parent_node) {
        const TreeNode* child_node = parent_node->child(row);
        if (child_node) {
            return createIndex(row, column, child_node);
        };
    };
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& index) const
{
    const TreeNode* child = getNode(index);
    if (child != &m_root) {
        const TreeNode* parent = child->parent();
        if (parent != &m_root) {
            return createIndex(parent->row(), 0, parent);
        };
    };
    return QModelIndex();
}

int TreeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ((role == Qt::DisplayRole) && (orientation == Qt::Horizontal)) {
        switch (section) {
        case 0: return "Item";
        case 1: return "thing";
        case 2: return "Unique ID";
        default:
            break;
        };
    };
    return QVariant();
}

void TreeModel::appendCharacter(const poe_api::Character& character)
{
    QModelIndex parent_index = createIndex(0, 0, &m_character_root);
    const int k = m_character_root.childCount();
    beginInsertRows(parent_index, k, k);
    m_character_root.addChild<CharacterNode>(character);
    endInsertRows();
}

void TreeModel::appendStash(const poe_api::StashTab& stash)
{
    QModelIndex parent_index = createIndex(0, 0, &m_stash_root);
    const int k = m_stash_root.childCount();
    beginInsertRows(parent_index, k, k);
    m_stash_root.addChild<StashNode>(stash);
    endInsertRows();
}
