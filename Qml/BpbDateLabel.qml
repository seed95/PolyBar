import QtQuick 2.0

Item
{
    width: date.contentWidth

    Text
    {
        id: date
        text: Qt.formatDateTime(new Date(),"MMM dd hh:mm")
        font.family: fontRobotoRegular.name
        font.pixelSize: 15
        color: "#dfdfdf"
    }

    Timer
    {
        interval: 6000
        repeat: true
        running: true

        onTriggered:
        {
            date.text = Qt.formatDateTime(new Date(),"MMM dd hh:mm")
        }
    }

}
