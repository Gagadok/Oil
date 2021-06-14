#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pythonfunctions.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MainWindow::makePlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::makePlot()
{
    QFile f("../odo.bin");
    f.open(QIODevice::ReadOnly);
    QDataStream in(&f);
    in.setByteOrder(QDataStream::LittleEndian);
    QVector<qint16> data;
    while(!in.atEnd()) {
    qint16 x;
    in >> x;
    data.append(x);
    }

    int dtSize = data.size();
    QVector<QVector<qint16>> dt;
    for (int i = 0; i < dtSize; i+=4)
    {
        QVector<qint16> tempDt;
        tempDt.append(data.value(i));
        tempDt.append(data.value(i + 1));
        tempDt.append(data.value(i + 2));
        tempDt.append(data.value(i + 3));
        dt.append(tempDt);
    }

    int c_scan_length = dt.size();
    PythonFunctions pf;
    QVector<double> xUnits = pf.linspace(0, c_scan_length - 1, c_scan_length);

    //np.zeros
    QVector<QVector<qint16>> increment;
    for (int i = 0; i < c_scan_length; i++)
    {
        QVector<qint16> temp;
        for (int j = 0; j < 4; j++)
        {
            temp.append(0);
        }
        increment.append(temp);
    }

    for (int i = 0; i < c_scan_length - 1; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            qint16 diff = dt.value(i).value(j) - dt.value(i + 1).value(j);
            if (diff < -4096)
            {
                diff += 8190;
            }
            increment[i + 1][j] = diff;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        increment[0][i] = increment[1][i];
    }

    QVector<double> odo_0;
    QVector<double> odo_1;
    QVector<double> odo_2;
    QVector<double> odo_3;
    for (int i = 0; i < c_scan_length; i++)
    {
        odo_0.append(increment[i][0]);
        odo_1.append(increment[i][1]);
        odo_2.append(increment[i][2]);
        odo_3.append(increment[i][3]);
    }

    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->customPlot->graph(0)->setData(xUnits, odo_0);
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setPen(QPen(Qt::yellow));
    ui->customPlot->graph(1)->setData(xUnits, odo_1);
    ui->customPlot->addGraph();
     ui->customPlot->graph(2)->setPen(QPen(Qt::green));
    ui->customPlot->graph(2)->setData(xUnits, odo_2);
    ui->customPlot->addGraph();
     ui->customPlot->graph(3)->setPen(QPen(Qt::red));
    ui->customPlot->graph(3)->setData(xUnits, odo_3);
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->graph(0)->rescaleAxes();
    ui->customPlot->graph(1)->rescaleAxes(true);
    ui->customPlot->graph(2)->rescaleAxes(true);
    ui->customPlot->graph(3)->rescaleAxes(true);
//    ui->customPlot->xAxis->setRange(-1, 1);
//    ui->customPlot->yAxis->setRange(0, 1);
    ui->customPlot->replot();
}
