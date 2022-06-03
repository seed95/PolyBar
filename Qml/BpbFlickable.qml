import QtQuick 2.0

Rectangle {
    id: container

    // Set this variables in qml
    property int direction: Qt.LeftToRight

    // Set this variables in cpp
    property string labelBackgroundColor: ""
    property bool   labelHaveUnderline: false
    property string labelTextColor: ""
    property string labelContent: ""
    property string labelActionString: ""

    // Cpp Signals
    signal executeAction(string action)

    color: "#000000"

    Flickable
    {
        id: flickbar
        width: parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
        clip: true

        ListView
        {
            id: lv
            height: parent.height
            width: parent.width
            anchors.topMargin: 15
            orientation: ListView.Horizontal
            layoutDirection: direction
            interactive: contentWidth>width
            model: ListModel
            {
                id: lm
            }
            delegate: BpbLabel
            {
                height: parent.height
                anchors.top: parent.top
                color_background: colorBackground
                underline: haveUnderline
                label_color: labelColor
                label_text: labelText
                label_action: labelAction

                onLabelClicked: executeAction(labelAction)
            }

            onFocusChanged: console.log(lv.width, lv.x)
        }
    }

    /*** Call this function from cpp ***/
    function clearLabels()
    {
        lm.clear()
    }

    function addLabel()
    {
        lm.append({
                      "colorBackground": container.labelBackgroundColor,
                      "haveUnderline": container.labelHaveUnderline,
                      "labelColor": container.labelTextColor,
                      "labelText": container.labelContent,
                      "labelAction": container.labelActionString
                  })
    }
}
