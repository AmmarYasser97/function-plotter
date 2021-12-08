#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functionevaluator.h"
#include <QtCharts>
#include <QDebug>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


