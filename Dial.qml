import QtQuick
import QtQuick.Controls as Controls
Item {
    id:root

    required property int level
    property bool active: false
    property string errorText: ""

    implicitWidth: 260
    implicitHeight: 300

    Controls.Dial{
        id:meter

        anchors.horizontalCenter: parent.horizontalCenter
        width: 220;height: 220

        from: 0;to: 100
        value: root.level

        enabled: false
        opacity: 1.0
    }
    Text{
        anchors.centerIn: meter
        text: root.level+"%"
        font.pixelSize: 34
        color: "#202124"
    }
    Text {
        anchors.top: meter.bottom
        anchors.topMargin: 18
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width

        text: root.errorText.length > 0
              ? root.errorText
              : root.active ? "Listening" : "Microphone stopped"

        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WordWrap
        font.pixelSize: 15
        color:root.errorText.length > 0 ? "#b3261e" : "#4b5563"
    }
}