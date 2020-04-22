#include "sinesweep.h"

#include <QAudioFormat>
#include <qmath.h>
#include <qendian.h>
Generator::Generator(const std::vector<double> &audio, const QAudioFormat &format
    , qint64 durationUs
    , int sampleRate)
{
    if (format.isValid())
        generateData(audio, format, durationUs, sampleRate);
}

void Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Generator::stop()
{
    m_pos = 0;
    close();
}

void Generator::generateData(const std::vector<double> &audio, const QAudioFormat &format, qint64 durationUs, int sampleRate)
{
//    const int channelBytes = format.sampleSize() / 8;
//    const int sampleBytes = format.channelCount() * channelBytes;
//    qint64 length = (format.sampleRate() * format.channelCount() * (format.sampleSize() / 8))
//                        * durationUs / 1000000;
//    Q_ASSERT(length % sampleBytes == 0);
//    Q_UNUSED(sampleBytes) // suppress warning in release builds
    qint64 length = audio.size();

    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int sampleIndex = 0;

    for (int i = 0; i < length; i++) {

        //const qreal x = qSin(2 * M_PI * sampleRate * qreal(sampleIndex++ % format.sampleRate()) / format.sampleRate());
        const qreal x = audio[i];
        for (int i=0; i<format.channelCount(); ++i) {
            if (format.sampleSize() == 8) {
                if (format.sampleType() == QAudioFormat::UnSignedInt) {
                    const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                    *reinterpret_cast<quint8 *>(ptr) = value;
                } else if (format.sampleType() == QAudioFormat::SignedInt) {
                    const qint8 value = static_cast<qint8>(x * 127);
                    *reinterpret_cast<qint8 *>(ptr) = value;
                }
            } else if (format.sampleSize() == 16) {
                if (format.sampleType() == QAudioFormat::UnSignedInt) {
                    quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        qToLittleEndian<quint16>(value, ptr);
                    else
                        qToBigEndian<quint16>(value, ptr);
                } else if (format.sampleType() == QAudioFormat::SignedInt) {
                    qint16 value = static_cast<qint16>(x * 32767);
                    if (format.byteOrder() == QAudioFormat::LittleEndian)
                        qToLittleEndian<qint16>(value, ptr);
                    else
                        qToBigEndian<qint16>(value, ptr);
                }
            }
            ptr += sizeof (double);
        }
    }
}

qint64 Generator::readData(char *data, qint64 len)
{
    qint64 total = 0;
    if (!m_buffer.isEmpty()) {
        while (len - total > 0) {
            const qint64 chunk = qMin((m_buffer.size() - m_pos), len - total);
            memcpy(data + total, m_buffer.constData() + m_pos, chunk);
            m_pos = (m_pos + chunk) % m_buffer.size();
            total += chunk;
        }
    }
    return total;
}

qint64 Generator::writeData(const char *data, qint64 len)
{
    Q_UNUSED(data);
    Q_UNUSED(len);

    return 0;
}

qint64 Generator::bytesAvailable() const
{
    return m_buffer.size() + QIODevice::bytesAvailable();
}

SineSweep::SineSweep()
{
    sample = std::vector<double>(numSamples, 0);
    generateTone();

}

void SineSweep::generateTone(){
    double currentFreq = 0, numerator;
    for (int i = 0; i < numSamples; ++i) {
        numerator = i / numSamples;
        currentFreq = startFrequency + (numerator * (endFrequency - startFrequency))*0.5;
        if ((i % 1000) == 0) {
            //emit freqPost(currentFreq);
        }
        sample[i] = std::sin(2*M_PI* i / (sampleRate / currentFreq));
    }
    initializeAudio(QAudioDeviceInfo::defaultOutputDevice());
}


void SineSweep::initializeAudio(const QAudioDeviceInfo &deviceInfo)
{
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    if (!deviceInfo.isFormatSupported(format)) {
        //qWarning() << "Default format not supported - trying to use nearest";
        format = deviceInfo.nearestFormat(format);
    }

    m_generator.reset(new Generator(sample, format, 600000,48000));
    m_audioOutput.reset(new QAudioOutput(deviceInfo,format));
    m_generator->start();

}

void SineSweep::generateSound(){

}
