import QtQuick 2.0

Rectangle {
    id: container

    property string labelBackgroundColor: ""
    property bool labelHaveUnderline: false
    property string labelTextColor: ""
    property string labelContent: ""
    property string labelActionString: ""

    //    Component.onCompleted: {
    //        addLabel()
    //        addLabel()
    //        addLabel()
    //        addLabel()
    //        addLabel()
    //        addLabel()
    //        addLabel()
    //        addLabel()
    //        addLabel()
    //    }
    Flickable {
        id: flickbar
        width: parent.width
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
        //        flickableDirection: Flickable.HorizontalFlick
        clip: true

        ListView {
            id: lv
            height: parent.height
            width: parent.width
            anchors.topMargin: 15
            model: ListModel {
                id: lm
            }
            delegate: PbLabel {
                height: parent.height
                anchors.top: parent.top
                color_background: colorBackground
                underline: haveUnderline
                label_color: labelColor
                label_text: labelText
                label_action: labelAction

                onLabelClicked: console.log("action", action)
            }

            orientation: ListView.Horizontal
            layoutDirection: Qt.LeftToRight
            //            spacing: 20
            //            interactive: false
        }
    }

    function addLabel() {
        lm.append({
                      "colorBackground": container.labelBackgroundColor,
                      "haveUnderline": container.labelHaveUnderline,
                      "labelColor": container.labelTextColor,
                      "labelText": container.labelContent,
                      "labelAction": container.labelActionString
                  })
    }
}
