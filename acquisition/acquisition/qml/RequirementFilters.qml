import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Requirements"
        filters: requirementFilters
    }
    GridLayout {
        id: requirementFilters
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 3
        visible: false

        Label { text: "Level" }
        TextField {
            id: minLevel
            inputMask: "99999"
            inputMethodHints: Qt.ImhDigitsOnly
            placeholderText: "Min";
            Layout.preferredWidth: 40;
            onTextChanged: { Acquisition.setMinLevel(parseInt(text, 10)) }
        }
        TextField {
            id: maxLevel
            placeholderText: "Max";
            inputMethodHints: Qt.ImhDigitsOnly
            Layout.preferredWidth: 40;
        }

        Label { text: "Stength" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Dexterity" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Intelligence" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Character Class" }
        ComboBox {
            model: Acquisition.searchFilters.characterClasses
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }
    }
}
