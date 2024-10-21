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
        ComboBox { model: Filter.ultimatumChallengeTypes }

        Label { text: "Reward Type" }
        ComboBox { model: Filter.ultimatumRewardTypes }

        Label { text: "Required Item" }
        ComboBox { model: Filter.ultimatumRequiredItems }

        Label { text: "Reward Unique" }
        ComboBox { model: Filter.ultimatumRewardUniques }
    }
}
