import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Dialogs
import QtQuick.Layouts

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: "Acquisition"
    /*

    //menuBar: MainMenuBar {}

    SplitView {
        id: splitView
        anchors.fill: parent
        anchors.margins: 0
        orientation: Qt.Horizontal

        ScrollView {
            id: searchFilterPanel
            anchors.margins: 0
            SplitView.minimumWidth: implicitWidth
            SplitView.maximumWidth: implicitWidth

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 0

                ComboBox {
                    Layout.fillWidth: true
                    model: ["Search Items"]
                }

                //TypeFilters {}
                //WeaponFilters {}
                //ArmourFilters {}
                //SocketFilters {}
                //RequirementFilters {}
                //MapFilters {}
                //HeistFilters {}
                //SanctumFilters {}
                //UltimatumFilters {}
                //MiscellaneousFilters {}

                Rectangle { Layout.fillHeight: true }
            }

        }

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

                //model: Acquisition.treeModel

                delegate: TreeViewDelegate {
                    id: itemViewDelegate
                    contentItem: Label {
                        text: itemViewDelegate.model.display
                    }
                }
            }
        }
    }
    */
}
