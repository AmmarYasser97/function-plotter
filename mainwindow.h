#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "functionevaluator.h"
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QtCharts>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  QLineSeries *series = new QLineSeries(); //  Define line chart to plot on it
  QChart *chart = new QChart();
  QChartView *chartView =
      new QChartView(chart); // Initiate chart view to render the line chart

  ~MainWindow();

private slots:
  void on_plotButton_clicked();

  void on_plotButton_released();

  void invalidEquation();

private:
  Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
