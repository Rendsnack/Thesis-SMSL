#ifndef GENERATOR_H
#define GENERATOR_H

#include <QIODevice>
#include "mode.h"


class Generator : public QIODevice
{
public:
    Generator();

public slots:
    std::vector<double> & generateSineSweep(std::vector<double> & storagePlace, int initialFrequency, int endFrequency, double duration, Mode mode);

private:

};

#endif // GENERATOR_H
