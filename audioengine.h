#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>
#include <QQmlEngine>
#include <QAudioSource>
#include <QMediaDevices>
#include <QIODevice>
class AudioEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int level READ level NOTIFY levelChanged FINAL)
public:
    explicit AudioEngine(QObject *parent = nullptr);
    int level()const;
signals:
    void levelChanged();
private:
    int m_level=0;

    QAudioSource *m_audioSource = nullptr;
    QIODevice *m_device = nullptr;
};

#endif // AUDIOENGINE_H
