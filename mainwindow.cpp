#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chartView->setRenderHint(QPainter::Antialiasing);
    ui->horizontalLayout->addWidget(chartView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_plotButton_clicked()
{
    QString equation = ui->equLine->text();
    float min_x = ui->minBox->value(), max_x = ui->maxBox->value();

    if(min_x > max_x) {
        QMessageBox msg;
        msg.information(this, "Function Plotter","Invalid Input.\nThe minimum value of x must be less than or equal the maximum value of x.");
        return;
    }

//    QRegExp rx("([+-]?\\[0-9]?\\*?[xX]\\^?\\[0-9]?)");
//    QValidator *equationValidaor = new QRegExpValidator(rx, this);
//    ui->equLine->setValidator(equationValidaor);

    FunctionEvaluator equ;
    equ.setEquation(equation);
    equ.setMinX(min_x);
    equ.setMaxX(max_x);

    series->append(equ.evaluatEquation());

    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle(equation);

}

void MainWindow::on_plotButton_released()
{
    chart->removeSeries(series);
    series->clear();
}
