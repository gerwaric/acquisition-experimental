import QtQuick
import QtQuick.Controls.Fusion

TextField {
	id: root
    required property var filter
    inputMethodHints: Qt.ImhDigitsOnly
	text: isNaN(root.filter.value) ? "" : root.filter.value.toFixed(0)
	onTextChanged: { root.filter.value = parseInt(text, 10) }
}
