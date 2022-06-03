import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.4
import Qt.labs.settings 1.0

Window {
    id: root

    visible: true
    width: 1500
    height: 30
    x: 0
    y: 0
    minimumHeight: height
    maximumHeight: height
    minimumWidth: width
    maximumWidth: width
    title: "PolyBar"
    color: "#dcdcdc"
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    // Fonts
    FontLoader
    {
        id: fontAwesomeSolid
        source: "qrc:/Fonts/fa6-solid.ttf"
    }
    FontLoader
    {
        id: fontAwesomeBrand
        source: "qrc:/Fonts/fa6-brands.ttf"
    }
    FontLoader
    {
        id: fontAwesomeRegular
        source: "qrc:/Fonts/fa6-reg.ttf"
    }
    FontLoader
    {
        id: fontRobotoRegular
        source: "qrc:/Fonts/Roboto-Regular.ttf"
    }

    // Main
    BpbFlickable
    {
        id: left_bar
        width: parent.width / 2
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
        direction: Qt.LeftToRight
        objectName: "LeftBar"
    }

    BpbFlickable
    {
        id: right_bar
        width: parent.width / 2
        height: parent.height
        anchors.right: parent.right
        anchors.top: parent.top
        direction: Qt.RightToLeft
        objectName: "RightBar"
    }

}
