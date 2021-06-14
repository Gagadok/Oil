#ifndef PYTHONFUNCTIONS_H
#define PYTHONFUNCTIONS_H

#include <QVector>

class PythonFunctions
{
public:
    PythonFunctions();
    QVector<double> linspace(double start, double end, int count);
};

#endif // PYTHONFUNCTIONS_H
