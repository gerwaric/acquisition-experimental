import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Dialogs
import QtQuick.Layouts

ApplicationWindow {
    width: 800
    height: 600
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
            ActionListMenu {
                title: "Current League"
                actions: Acquisition.leagueActions
            }
            Action {
                text: "Refresh League List"
                onTriggered: Acquisition.getLeagues()
            }
        }

        ActionListMenu {
            id: refreshMenu
            title: "Refresh"
            actions: Acquisition.refreshActions
        }

        Menu {
            id: loggingMenu
            title: "Logging"
            ActionListMenu {
                title: "Level"
                actions: Acquisition.loggingActions
            }
            MenuSeparator {}
            Action {
                text: "Reset to default"
                onTriggered: Acquisition.restoreDefaultLogLevel()
            }

            Action {
                text: "Open log file";
                onTriggered: Acquisition.openLogFile()
            }
        }
    }

    SplitView {
        id: splitView
        anchors.fill: parent
        anchors.margins: 0
        orientation: Qt.Horizontal

        EquipableSearchFilters {}

        ColumnLayout {
            id: resultsPanel
            SplitView.fillWidth: true

            HorizontalHeaderView {
                id: itemsHeader
                clip: true
                syncView: itemsView
                Layout.fillWidth: true
            }

            TreeView {
                id: itemsView
                clip: true
                boundsMovement: Flickable.StopAtBounds

                Layout.fillWidth: true
                Layout.fillHeight: true

                ScrollBar.horizontal: ScrollBar {}
                ScrollBar.vertical: ScrollBar {}

                model: Acquisition.treeModel

                delegate: TreeViewDelegate {
                    id: itemViewDelegate
                    contentItem: Label {
                        text: itemViewDelegate.model.display
                    }
                }
            }
        }
    }
}
