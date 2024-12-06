import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Attributes"
        filters: attributeFilters
    }
    GridLayout {
        id: attributeFilters
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 3
        visible: false

        Label {
			text: "+# to Total:"
            Layout.margins: 5
            Layout.columnSpan: 3
        }

        Label { text: "Strength" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Dexterity" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Intelligence" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label {
			text: "#% Increased:"
            Layout.margins: 5
            Layout.columnSpan: 3
        }

        Label { text: "Strength" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Dexterity" }
        TextField {
            placeholderText: "Min"
            Layout.preferredWidth: 40
        }
        TextField {
            placeholderText: "Max"
            Layout.preferredWidth: 40
        }

        Label { text: "Intelligence" }
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

