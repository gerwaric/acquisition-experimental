import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Frame {
    id: root
    Layout.minimumHeight: 100
    required property string title
    required property int columns

    //required property Component content

    default property alias data: grid.data

    Layout.fillWidth: true

    ColumnLayout {
        anchors.fill: parent

        Button {
            id: header
            text: root.title
            Layout.columnSpan: root.columns
            Layout.fillWidth: true
            onClicked: {
                grid.visible = !grid.visible
            }
        }

        GridLayout {
            id: grid
            columns: root.columns
        }
    }
}

