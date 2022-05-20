import QtQuick 2.10
import QtQuick.Window 2.10
import QtQuick.Controls 2.4
import Qt.labs.settings 1.0

Window {
    id: root

    property bool rtl: true //Right to Left
    property bool fontOffset: true
    property bool devMode: false //Development mode

    property string domain: "lolo.com"
    property string base_id: "lolo.com"
    property string app_status: "Updated from server 12:20PM"
    property string login_status: "Server connected"

    //Error properties
    property string error_text: ""
    property int error_duration: 100

    //User properties
    property int idUser: 103
    property string firstname: "علی"
    property string lastname: "عدنان"
    property string username: "Adnan"
    property string lastlogin: "2020/08/19 12:23:43"
    property int status: 0
    property string bio: "Bio"
    property string image: "Image"
    property int idDepartment: 8

    //Properties for news
    property string news_title1: ""
    property string news_content1: ""
    property string news_date1: ""
    property string news_title2: ""
    property string news_content2: ""
    property string news_date2: ""

    signal loginUser(string username, string pass)
    signal replyButtonClicked
    signal archiveButtonClicked
    signal scanButtonClicked
    signal flagButtonClicked(int id)

    visible: true
    width: 1500
    height: 50
    x: 0
    y: 0
    minimumHeight: height
    maximumHeight: height
    minimumWidth: width
    maximumWidth: width
    title: "Document Manager"
    color: "#dcdcdc"
    //    flags: Qt.FramelessWindowHint

    //Fonts:
    FontLoader {
        id: fontAwesomeSolid
        source: "qrc:/Fonts/fa6-solid.ttf"
    }
    FontLoader {
        id: fontAwesomeBrand
        source: "qrc:/Fonts/fa6-brands.ttf"
    }
    FontLoader {
        id: fontAwesomeRegular
        source: "qrc:/Fonts/fa6-reg.ttf"
    }

    PbFlickable {
        width: parent.width / 2
        height: parent.height
        anchors.left: parent.left
        anchors.top: parent.top
        objectName: "LeftBar"
    }

    //Functions
    /*** Call this functions from cpp ***/
    function loginSuccessfully() {
        animateHideLogin.start()
    }

    //call this function when have a error and must be
    //set properites `error_text`, `error_duration`.
    function showMessage() {
        error_messae.showMessage(error_text, error_duration)
    }

    /*** Call this function from qml ***/
    function signOut() {
        login.visible = true
        animateShowLogin.start()
        page.signOut()
    }

    /*** Utilities functions ***/
    function isAdmin() {
        return root.username.toLowerCase() === "admin"
    }

    //Slice string from 0 with amount len
    //and add '...' to end text
    function sliceString(text, len) {
        if (text.length > len) {
            return text.slice(0, len) + "..."
        }
        return text
    }

    //Convert english number to arabic number
    function en2ar(number) {
        number = number.toString()
        var arabic_numbers = ['٠', '١', '٢', '٣', '٤', '٥', '٦', '٧', '٨', '٩'] //arabic_numbers[0] = 0, arabic_numbers[9] = 9
        //        console.log('0:', arabic_numbers[0], ",1:", arabic_numbers[1], ",9:", arabic_numbers[9])
        var english_numbers = [/0/g, /1/g, /2/g, /3/g, /4/g, /5/g, /6/g, /7/g, /8/g, /9/g]
        for (var i = 0; i < 10; i++) {
            number = number.replace(english_numbers[i], arabic_numbers[i])
        }
        return number
    }

    //Convert arabic number to english number
    function ar2en(number) {
        number = number.toString()
        var w_numbers = [/۰/g, /۱/g, /۲/g, /۳/g, /۴/g, /۵/g, /۶/g, /۷/g, /۸/g, /۹/g]
        var arabic_numbers = [/٠/g, /١/g, /٢/g, /٣/g, /٤/g, /٥/g, /٦/g, /٧/g, /٨/g, /٩/g]
        var en_number
        for (var i = 0; i < 10; i++) {
            number = number.replace(w_numbers[i],
                                    i).replace(arabic_numbers[i], i)
        }
        return number
    }
}
