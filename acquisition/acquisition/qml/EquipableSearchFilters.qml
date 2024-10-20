import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ScrollView {
id: searchFilterPanel
anchors.margins: 0
SplitView.minimumWidth: implicitWidth

    ColumnLayout {

        ComboBox {
            model: ["Search Items"]
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Type Filters"
                onClicked: {
                    typeFilters.visible = !typeFilters.visible
                }
            }
            GridLayout {
                id: typeFilters
                Layout.fillWidth: true
                Layout.margins: 5
                columns: 2
                visible: false

                Label { text: "Item Category" }
                ComboBox { model: Filter.itemCategories }

                Label { text: "Item Rarity" }
                ComboBox { model: Filter.itemRarities }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Weapon Filters"
                onClicked: {
                    weaponFilters.visible = !weaponFilters.visible
                }
            }
            GridLayout {
                id: weaponFilters
                Layout.fillWidth: true
                Layout.margins: 5
                columns: 3
                visible: false

                Label { text: "Damage" }
                TextEdit { text: "Min"; inputMethodHints: Qt.ImhFormattedNumbersOnly }
                TextEdit { text: "Max"; inputMethodHints: Qt.ImhFormattedNumbersOnly }

                Label { text: "Critical Chance" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Physical DPS" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Attacks per Second" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Damage per Second" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Elemental DPS" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Armour Filters"
                onClicked: {
                    armourFilters.visible = !armourFilters.visible
                }
            }
            GridLayout {
                id: armourFilters
                Layout.fillWidth: true
                Layout.margins: 5
                columns: 3
                visible: false

                Label { text: "Armour" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Energy Shield" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Block" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Evasion" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Ward" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Base Percentile" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Socket Filters"
                onClicked: {
                    socketFilters.visible = !socketFilters.visible
                }
            }
            GridLayout {
                id: socketFilters
                Layout.fillWidth: true
                Layout.margins: 5
                columns: 7
                visible: false

                Label { text: "Sockets" }
                TextEdit { text: "R" }
                TextEdit { text: "G" }
                TextEdit { text: "B" }
                TextEdit { text: "W" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Links" }
                TextEdit { text: "R" }
                TextEdit { text: "G" }
                TextEdit { text: "B" }
                TextEdit { text: "W" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Requirements"
                onClicked: {
                    requirementFilters.visible = !requirementFilters.visible
                }
            }
            GridLayout {
                id: requirementFilters
                Layout.fillWidth: true
                Layout.margins: 5
                columns: 3
                visible: false

                Label { text: "Level" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Stength" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Dexterity" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Intelligence" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Character Class" }
                ComboBox { model: Filter.characterClasses; Layout.columnSpan: 2 }
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Map Filters (TBD)"
                enabled: false
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Sanctum Filters (TBD)"
                enabled: false
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Ultimatum Filters (TBD)"
                enabled: false
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Button {
                Layout.fillWidth: true
                text: "Miscellaneous"
                onClicked: {
                    miscelanneousFilters.visible = !miscelanneousFilters.visible
                }
            }
            GridLayout {
                id: miscelanneousFilters
                Layout.fillWidth: true
                Layout.margins: 5
                columns: 3
                visible: false

                Label { text: "Item Level" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Quality" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Gem Level" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Gem Experience" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Transfigured Gem" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Vaal Gem" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Corpse Type" }
                ComboBox { model: Filter.corpseTypes; Layout.columnSpan: 2 }

                Label { text: "Crucible Item" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Fractured Item" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Synthesized Item" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Searing Exarch Item" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Eater of Worlds Item" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Identified" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Corrupted" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Mirrored" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Split" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Crafted" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Veiled" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Foreseeing" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Talisman Tier" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Stored Experience" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Stack Size" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }

                Label { text: "Alternate Art" }
                ComboBox { model: ["Any","Yes","No"]; Layout.columnSpan: 2 }

                Label { text: "Fail Variation" }
                ComboBox { model: Filter.foilVariations; Layout.columnSpan: 2 }

                Label { text: "Scourge Tier" }
                TextEdit { text: "Min" }
                TextEdit { text: "Max" }
            }
        }

        Rectangle {
            id: searchPanelFiller
            Layout.fillHeight: true
        }
    }
}
