import QtQuick
import QtQuick.Controls.Fusion

MenuBar {
    id: rootMenu

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
