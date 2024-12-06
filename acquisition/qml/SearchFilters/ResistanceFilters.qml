//import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Resistances"
        filters: resistanceFilters
    }
    GridLayout {
        id: resistanceFilters
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 3
        visible: false

        Label {
			text: "+#% to Total:"
            Layout.margins: 5
            Layout.columnSpan: 3
        }

        Label { text: "Fire" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Cold" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Lightning" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Chaos" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label {
			text: "+#% to Maximum:"
            Layout.margins: 5
            Layout.columnSpan: 3
        }

        Label { text: "Fire" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Cold" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Lightning" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Chaos" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }


    }
}

