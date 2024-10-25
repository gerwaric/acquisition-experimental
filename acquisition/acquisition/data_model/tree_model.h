#pragma once

#include <acquisition/api_types/character.h>
#include <acquisition/api_types/item.h>
#include <acquisition/api_types/stash_tab.h>
#include <acquisition/data_model/tree_node.h>

#include <QsLog/QsLog.h>

#include <QAbstractItemModel>

class TreeModel : public QAbstractItemModel {
    Q_OBJECT

public:

    explicit TreeModel(QObject* parent = nullptr);
    ~TreeModel() override {};

    // Returns the index of the item in the model specified by the given row, column and parent index.
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

    // Returns the parent of the model item with the given index. If the item has no parent, an invalid QModelIndex is returned.
    QModelIndex parent(const QModelIndex& index) const override;
    
    // Returns the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
    inline int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return getNode(parent)->childCount();
    };
    
    // Returns the number of columns for the children of the given parent.
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    
    // Returns the data stored under the given role for the item referred to by the index.
    inline QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        return (index.isValid() && (role == Qt::DisplayRole))
            ? getNode(index)->data(index.column())
            : QVariant();
    };

    inline bool hasChildren(const QModelIndex &parent = QModelIndex()) const override {
        return getNode(parent)->hasChildren();
    };

    // Returns the data for the given role and section in the header with the specified orientation.
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void appendStash(const poe_api::StashTab& stash);
    void appendCharacter(const poe_api::Character& character);

    inline const TreeNode* getNode(const QModelIndex& index) const {
        return index.isValid() ? static_cast<TreeNode*>(index.internalPointer()) : &m_root;
    };

private:

    TreeNode m_root;
    TreeNode& m_character_root;
    TreeNode& m_stash_root;
};
