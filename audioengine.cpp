#include "audioengine.h"

#include <QAudioDevice>
#include <QMediaDevices>
#include <QtGlobal>
#include <cmath>

AudioEngine::AudioEngine(QObject *parent)
    : QObject{parent}
{
    startAudio();
}

int AudioEngine::level() const
{
    return m_level;
}

bool AudioEngine::active()const
{
    return m_active;
}
QString AudioEngine::errorString()const
{
    return m_errorString;
}
void AudioEngine::startAudio(){
    const QAudioDevice inputDevice=QMediaDevices::defaultAudioInput();

    if(inputDevice.isNull()){
        setErrorString("No microphone detected");
        setActive(false);
        return;
    }

    m_format=inputDevice.preferredFormat();

    if(!m_format.isValid()){
        m_format.setSampleRate(44100);
        m_format.setChannelCount(1);
        m_format.setSampleFormat(QAudioFormat::Int16);
    }
    if(!inputDevice.isFormatSupported(m_format)){
        setErrorString("Microphone format is not supported");
        setActive(false);
        return;
    }

    m_audioSource = new QAudioSource(inputDevice,m_format,this);
    m_device = m_audioSource->start();

    if(!m_device){
        setErrorString(QString("Could not start microphone. Error code: %1").arg(static_cast<int>(m_audioSource->error())));
        setActive(false);
        return;
    }
    connect(m_device,&QIODevice::readyRead,this,&AudioEngine::handleReadyRead);

    setErrorString(QString());
    setActive(true);
}
void AudioEngine::handleReadyRead()
{
    const QByteArray data = m_device->readAll();
    if(data.isEmpty())
        return;
    setLevel(calculateLevel(data));
}
int AudioEngine::calculateLevel(const QByteArray &data)
{
    const int bytesPerFrame=m_format.bytesPerFrame();
    const int bytesPerSample=m_format.bytesPerSample();
    const int channelCount=m_format.channelCount();

    if(bytesPerFrame<=0 || bytesPerSample<=0 || channelCount<=0)
        return 0;
    const int frameCount=m_format.framesForBytes(data.size());
    const char *buffer=data.constData();

    double sumSquares=0.0;
    int sampleCount=0;

    for(int frame=0;frame<frameCount;++frame){
        const char *frameData=buffer+frame*bytesPerFrame;

        for(int channel=0;channel<channelCount;++channel){
            const char *sampleData=frameData+channel*bytesPerSample;
            const float sample=m_format.normalizedSampleValue(sampleData);
            sumSquares+=sample*sample;
            ++sampleCount;
        }
    }
    if(sampleCount==0)
        return 0;
    const double rms=std::sqrt(sumSquares/sampleCount);
    const int targetLevel=qBound(0,qRound(rms*300.0),100);

    m_smoothedLevel=(m_smoothedLevel*0.75)+(targetLevel*0.25);
    return qBound(0,qRound(m_smoothedLevel),100);
}
void AudioEngine::setLevel(int level)
{
    if(m_level==level)
        return;
    m_level=level;
    emit levelChanged();
}
void AudioEngine::setActive(bool active){
    if(m_active==active)
        return;
    m_active=active;
    emit activeChanged();
}
void AudioEngine::setErrorString(const QString &errorString)
{
    if(m_errorString==errorString)
        return;
    m_errorString=errorString;
    emit errorStringChanged();
}