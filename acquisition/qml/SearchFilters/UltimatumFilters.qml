import QtQuick
import QtQuick.Controls.Fusion
import QtQuick.Layouts

ColumnLayout {
    Layout.fillWidth: true
    FilterSectionHeader {
        title: "Ultimatum Filters"
        filters: ultimatumFilters
    }
    GridLayout {
        id: ultimatumFilters
        Layout.fillWidth: true
        Layout.margins: 5
        columns: 2
        visible: false

        Label { text: "Challenge Type" }
        ComboBox { model: Acquisition.searchFilters.ultimatumChallengeTypes }

        Label { text: "Reward Type" }
        ComboBox { model: Acquisition.searchFilters.ultimatumRewardTypes }

        Label { text: "Required Item" }
        ComboBox { model: Acquisition.searchFilters.ultimatumRequiredItems }

        Label { text: "Reward Unique" }
        ComboBox { model: Acquisition.searchFilters.ultimatumRewardUniques }
    }
}
