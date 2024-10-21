import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Map Filters"
        filters: mapFilters
    }
    GridLayout {
        id: mapFilters
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 3
        visible: false

        Label { text: "Map Tier" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Map Packsize" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Map IIQ" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Map IIR" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Area Level" }
        TextField { placeholderText: "Min"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }
        TextField { placeholderText: "Max"; Layout.preferredWidth: 40; inputMethodHints: Qt.ImhDigitsOnly }

        Label { text: "Map Series" }
        ComboBox {
            model: Filter.mapSeries
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Blighted Map" }
        ComboBox {
            model: ["Any","Yes","No"];
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Blight-Ravaged Map" }
        ComboBox {
            model: ["Any","Yes","No"];
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

        Label { text: "Map Completion Reward" }
        ComboBox {
            model: Filter.mapCompletionRewards
            Layout.columnSpan: 2
            Layout.fillWidth: true
        }

    }
}
