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

    Menu {
        id: refreshMenu
        title: "Refresh"

        Action {
            text: "Update the Stash index"
            onTriggered: Acquisition.refreshCharacterIndex()
        }
        Action {
            text: "Update the Character index"
            onTriggered: Acquisition.refreshCharacterIndex()
        }
        Action {
            text: "Update both indexes"
            onTriggered: Acquisition.refreshAllIndexes()
        }

        MenuSeparator {}

        Action {
            text: "Refresh Stashes"
            onTriggered: Acquisition.refreshStashes()
        }
        Action {
            text: "Refresh Characters"
            onTriggered: Acquisition.refreshCharacters()
        }
        Action {
            text: "Refresh both"
            onTriggered: Acquisition.refreshCharactersAndStashes()
        }

        MenuSeparator {}

        Action {
            text: "Refresh Everything"
            onTriggered: Acquisition.refreshEverything()
        }
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
            text: "Reset logging to default level"
            onTriggered: Acquisition.restoreDefaultLogLevel()
        }

        Action {
            text: "Open the current log file"
            onTriggered: Acquisition.openLogFile()
        }
    }
}
