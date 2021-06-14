#include "pythonfunctions.h"

PythonFunctions::PythonFunctions()
{
}

QVector<double> PythonFunctions::linspace(double start, double end, int count)
{
    QVector<double> r;
    r.reserve(count);
    double step = (end - start) / (count-1);
    for (int i = 0; i < count ; i++)
    {
        r.append(start + i * step);
    }
    return r;
}
