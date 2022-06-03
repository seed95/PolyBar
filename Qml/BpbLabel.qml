import QtQuick 2.0

Rectangle {
    id: container

    property color color_background: "#f0f0f0"
    property bool underline: false
    property color label_color: "#aaaaaa"
    property string label_text: ""
    property string label_action: "action"

    // Qml Signals
    signal labelClicked()

    width: label.contentWidth
    color: color_background

    Text
    {
        id: label
        text: container.label_text
        anchors.centerIn: parent
        anchors.verticalCenterOffset: -1
        font.family: fontAwesomeSolid.name
        font.pixelSize: 15
        color: container.label_color
        font.underline: container.underline
    }

    MouseArea
    {
        anchors.fill: parent
        cursorShape:
        {
            if (container.label_action != "")
            {
                Qt.PointingHandCursor
            }
            else
            {
                Qt.ArrowCursor
            }
        }
        enabled: container.label_action != ""

        onClicked: labelClicked()
    }
}
