#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <QObject>
#include <QQmlEngine>

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
};

#endif // AUDIOENGINE_H
