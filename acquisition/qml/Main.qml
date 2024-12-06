import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Dialogs
import QtQuick.Layouts

import "SearchFilters" as SearchFilters

ApplicationWindow {
    width: 800
    height: 600
    visible: true
    title: "Acquisition"

    menuBar: MainMenuBar {}

    footer: RowLayout {
        Label { text: "Status:" }
        Label { text: Acquisition.statusText; Layout.fillWidth: true }
    }

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

                Label {
                    text: "Trade Filters"
                    Layout.fillWidth: true
                }

				SearchFilters.TypeFilters {}
				SearchFilters.WeaponFilters {}
				SearchFilters.ArmourFilters {}
				SearchFilters.SocketFilters {}
				SearchFilters.RequirementFilters {}
				SearchFilters.MapFilters {}
				SearchFilters.HeistFilters {}
				SearchFilters.SanctumFilters {}
				SearchFilters.UltimatumFilters {}
				SearchFilters.MiscellaneousFilters {}

                Label {
                    text: "Common Stats"
                    Layout.fillWidth: true
                }

				SearchFilters.AttributeFilters {}
				SearchFilters.ResistanceFilters {}

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

                model: Acquisition.searchResultsModel

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
