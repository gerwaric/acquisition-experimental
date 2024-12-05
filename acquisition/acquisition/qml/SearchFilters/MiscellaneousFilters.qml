import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Miscellaneous"
        filters: miscellaneousFilters
    }
    GridLayout {
        id: miscellaneousFilters
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 3
        visible: false

        Label { text: "Item Level" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Quality" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Gem Level" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Gem Experience" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 80; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 80; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Transfigured Gem" }
        ComboBox {
            model: ["Any","Yes","No"];
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Vaal Gem" }
        ComboBox {
            model: ["Any","Yes","No"];
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Corpse Type" }
        ComboBox {
            model: Acquisition.searchFilters.corpseTypes
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Crucible Item" }
        ComboBox {
            model: ["Any","Yes","No"];
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Fractured Item" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Synthesized Item" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Searing Exarch Item" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Eater of Worlds Item" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Identified" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Corrupted" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Mirrored" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Split" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Crafted" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Veiled" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Foreseeing" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Talisman Tier" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Stored Experience" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Stack Size" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Alternate Art" }
        ComboBox {
            model: ["Any","Yes","No"]
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Fail Variation" }
        ComboBox {
            model: Acquisition.searchFilters.foilVariations
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Scourge Tier" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
    }
}
