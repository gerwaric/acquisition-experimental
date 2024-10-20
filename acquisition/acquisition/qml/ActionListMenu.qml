import QtQuick
import QtQuick.Controls

Menu {
    id: automaticMenu

    required property var actions

    Repeater {
        model: automaticMenu.actions
        delegate: MenuItem {
            text: modelData.text
            checkable: modelData.checkable
            checked: modelData.checked
            onTriggered: modelData.trigger()
        }
    }
}
