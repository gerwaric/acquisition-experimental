import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.margins: 0
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Type Filters"
        filters: typeFilters
    }
    GridLayout {
        id: typeFilters
        visible: false
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 2

        Label { text: "Item Category"; }
        ComboBox { model: Filter.itemCategories; }

        Label { text: "Item Rarity" }
        ComboBox { model: Filter.itemRarities }
    }
}
