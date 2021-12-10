#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "functionevaluator.h"
#include <QtCharts>
#include <QDebug>
#include <QRegExpValidator>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QLineSeries* series = new QLineSeries();
    QChart *chart = new QChart();
    QChartView *chartView = new QChartView(chart);

    ~MainWindow();

private slots:
    void on_plotButton_clicked();

    void on_plotButton_released();

    void invalidEquation();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
