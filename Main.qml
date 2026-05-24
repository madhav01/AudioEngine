import QtQuick
import AudioEngine
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Audio Engine")
    AudioEngine{
        id:audio
    }

    Dial{
        anchors.centerIn: parent
        level:audio.level
        active:audio.active
        errorText:audio.errorString
    }



}
