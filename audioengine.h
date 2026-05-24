#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>
#include <QQmlEngine>
#include <QAudioSource>
#include <QMediaDevices>
#include <QIODevice>
#include <QString>
class AudioEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(int level READ level NOTIFY levelChanged FINAL)
    Q_PROPERTY(bool active READ active  NOTIFY activeChanged FINAL)
    Q_PROPERTY(QString errorString READ errorString  NOTIFY errorStringChanged FINAL)
public:
    explicit AudioEngine(QObject *parent = nullptr);

    int level()const;
    bool active()const;
    QString errorString()const;

signals:
    void levelChanged();
    void activeChanged();
    void errorStringChanged();

private:
    void startAudio();
    void handleReadyRead();
    int calculateLevel(const QByteArray &data);
    void setLevel(int level);
    void setActive(bool active);
    void setErrorString(const QString &setErrorString);

    int m_level=0;
    bool m_active=false;
    double m_smoothedLevel=0.0;
    QString m_errorString;
    QAudioFormat m_format;

    QAudioSource *m_audioSource = nullptr;
    QIODevice *m_device = nullptr;
};

#endif // AUDIOENGINE_H
