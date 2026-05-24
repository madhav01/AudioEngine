import QtQuick
import QtQuick.Controls
import AudioEngine
Item {
    AudioEngine{
        id:audio
    }

    Dial{
        from: 0;to: 100
        value: audio.level
    }
}
