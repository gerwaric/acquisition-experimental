import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    id: panel
    required property string title
    required property Component content

    Layout.fillWidth: true

    ColumnLayout {
        Button {
            text: panel.title
            Layout.fillWidth: true
            onClicked: {
                panelContent.visible = !panelContent.visible
            }
        }
        Loader {
            id: panelContent
            sourceComponent: panel.content
        }
    }
}
