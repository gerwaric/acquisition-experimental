import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Layouts

ApplicationWindow {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: "Acquisition"

    menuBar: MenuBar {
        id: mainWindowMenuBar

        Menu {
            id: authMenu
            title: "Login"
            Action {
                text: "Authenticate with OAuth"
                onTriggered: Acquisition.authenticate()
            }
        }

        Menu {
            id: leagueMenu
            title: "League"
            Repeater {
                model: Acquisition.leagueMenuActions  // Binding to the dynamic actions list
                delegate: MenuItem {
                    text: modelData.text
                    checkable: modelData.checkable
                    checked: modelData.checked
                    onTriggered: modelData.trigger()
                }
            }
            MenuSeparator {}
            Action {
                text: "Refresh Leagues"
            }
        }

        Menu {
            id: refreshMenu
            title: "Refresh"
        }

        Menu {
            id: logLevelMenu
            title: "Log Level"
            Repeater {
                model: Acquisition.loggingMenuActions
                delegate: MenuItem {
                    text: modelData.text
                    checkable: modelData.checkable
                    checked: modelData.checked
                    onTriggered: modelData.triggered()
                }
            }
            MenuSeparator {}
            Action {
                text: "Open log file";
                onTriggered: Acquisition.openLogFile()
            }
        }
    }

    RowLayout {
        id: mainWindowLayout
        anchors.fill: parent
        anchors.margins: 0

        Rectangle {
            id: treeSidePanelContainer
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft
            Layout.preferredWidth: button1.implicitWidth
            Layout.margins: 10

            ColumnLayout {
                id: treeSidePanel
                anchors.top: parent.top

                Label {
                    id: leagueComboBoxLabel
                    text: "League:"
                }

                Button {
                    id: button1
                    text: "Button 1 with Longer Text"
                    Layout.fillWidth: true
                }

                Button {
                    id: button3
                    text: "Button 3 with Longer Text"
                    Layout.fillWidth: true
                }
            }
        }

        Rectangle {
            id: treeViewContainer
            Layout.fillWidth: true
            Layout.fillHeight: true

            HorizontalHeaderView {
                id: treeHeader
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                syncView: treeView
            }

            TreeView {
                id: treeView
                anchors.top: treeHeader.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                clip: true
                boundsMovement: Flickable.StopAtBounds

                ScrollBar.horizontal: ScrollBar {}
                ScrollBar.vertical: ScrollBar {}

                model: Acquisition.treeModel

                delegate: TreeViewDelegate {
                    id: treeViewDelegate
                    contentItem: Label {
                        text: treeViewDelegate.model.display
                    }
                }
            }
        }
    }

    MessageDialog {
        id: infoDialog
        title: "Information"
        text: "This is an informational message."
        //icon: StandardIcon.Information
        //standardButtons: StandardButton.Ok

        onAccepted: {
            console.log("Dialog accepted (OK clicked)")
        }
    }

}
