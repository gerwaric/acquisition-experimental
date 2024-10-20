import QtQuick
import QtQuick.Controls

Item {
    id: root

    required property string title

    Label {
        text: root.title
        parent: root.parent
    }

    TextEdit {
        text: "Min"
        parent: root.parent
    }

    TextEdit {
        text: "Max"
        parent: root.parent
    }
}
