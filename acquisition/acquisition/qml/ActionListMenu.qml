import QtQuick
import QtQuick.Controls.Fusion

Menu {
    id: menuRoot

    required property var actions

    Repeater {
        model: menuRoot.actions
        delegate: MenuItem {
            text: modelData.text
            checkable: modelData.checkable
            checked: modelData.checked
            onTriggered: modelData.trigger()
        }
    }
}
