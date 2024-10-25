import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

RowLayout {
    id: root
    required property string title
    required property GridLayout filters
    CheckBox {
        padding: 0
        onCheckedChanged: {
            typeFiltersButton.enabled = checked
            root.filters.visible = checked
        }
    }
    Button {
        id: typeFiltersButton
        enabled: false
        Layout.fillWidth: true
        text: root.title
        onClicked: {
            root.filters.visible = !root.filters.visible
        }
    }
}
