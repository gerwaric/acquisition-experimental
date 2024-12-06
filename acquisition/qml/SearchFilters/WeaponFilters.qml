import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Weapon Filters"
        filters: weaponFilters
    }
    GridLayout {
        id: weaponFilters
        visible: false
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 3

        Label { text: "Damage" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }

        Label { text: "Critical Chance" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }

        Label { text: "Physical DPS" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }

        Label { text: "Attacks per Second" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }

        Label { text: "Damage per Second" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }

        Label { text: "Elemental DPS" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }

        Label { text: "Chaos DPS" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhFormattedNumbersOnly }
    }
}
