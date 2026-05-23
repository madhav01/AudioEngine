#include "audioengine.h"

#include <QAudioFormat>
#include <QtEndian>
#include <QtMath>

AudioEngine::AudioEngine(QObject *parent)
    : QObject{parent}
{
    QAudioFormat format;

    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);

    m_audioSource = new QAudioSource(format, this);

    m_device = m_audioSource->start();

    connect(m_device, &QIODevice::readyRead, this, [this]()
            {
                QByteArray data = m_device->readAll();

                if (data.isEmpty())
                    return;

                const int16_t *samples =
                    reinterpret_cast<const int16_t*>(data.constData());

                const int sampleCount =
                    data.size() / sizeof(int16_t);

                int peak = 0;

                for (int i = 0; i < sampleCount; ++i)
                {
                    int value = qAbs(samples[i]);

                    if (value > peak)
                        peak = value;
                }

                int level =
                    (peak * 100) / 32767;

                if (m_level == level)
                    return;

                m_level = level;

                emit levelChanged();
            });
}

int AudioEngine::level() const
{
    return m_level;
}