import QtQuick
import QtQuick.Controls.Fusion

TextField {
    required property var filter
    inputMethodHints: Qt.ImhDigitsOnly
    text: isNaN(filter.value) ? "" : filter.value.toFixed(0)
    onTextChanged: { filter.value = parseInt(text, 10) }
}
