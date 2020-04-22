#ifndef WAVFILE_H
#define WAVFILE_H
#include <QObject>
#include <QFile>
#include <QAudioFormat>
#include "QDataStream"

class WavPcmFile : public QFile {
public:
    WavPcmFile(const QString & name, const QAudioFormat & format, QObject *parent = nullptr);
    bool open();
    void writeHeader();
    qint64 write(const QByteArray &data);
    void close();

private:
    bool hasSupportedFormat();
    QAudioFormat format;
};

#endif // WAVFILE_H
