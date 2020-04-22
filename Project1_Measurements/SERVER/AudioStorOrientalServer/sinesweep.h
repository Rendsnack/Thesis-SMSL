#ifndef SINESWEEP_H
#define SINESWEEP_H

#include <QAudioDeviceInfo>
#include <QAudioOutput>
#include <QIODevice>
#include <QObject>
#include <math.h>

class Generator : public QIODevice{
    Q_OBJECT

public:
    Generator( const std::vector<double> &audio, const QAudioFormat &format, qint64 durationUs, int sampleRate);

    void start();
    void stop();

    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
    qint64 bytesAvailable() const override;

private:
    void generateData(const std::vector<double> &audio, const QAudioFormat &format, qint64 durationUs, int sampleRate);

private:
    qint64 m_pos = 0;
    QByteArray m_buffer;
};

class SineSweep : public QObject
{
    Q_OBJECT
public:
    SineSweep();
    void generateSound();

signals:
    void freqPost(double currentFreq);

private:
    void generateTone();
    void convertToPCM();
    void initializeAudio(const QAudioDeviceInfo &deviceInfo);

private:
    int sampleRate = 48000;
    double startFrequency = 0.1;
    double endFrequency = 12000;
    float numSamples = 6*48000;
    std::vector<double> sample;
    QScopedPointer<Generator> m_generator;
    QScopedPointer<QAudioOutput> m_audioOutput;




};

#endif // SINESWEEP_H
