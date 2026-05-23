#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>
#include <QQmlEngine>

class AudioEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit AudioEngine(QObject *parent = nullptr);

signals:
};

#endif // AUDIOENGINE_H
