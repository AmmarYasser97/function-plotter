#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  // Render the chart to be visible on the UI
  chartView->setRenderHint(QPainter::Antialiasing);
  ui->horizontalLayout->addWidget(chartView);

  // Define a RegExp to validate the input equation terms, every term must be on
  // this form (sign magnitude*X^power) except the first term can defined
  // without a sign e.g. 3*X^2 + 5*X
  QRegExp rx("([+-]?[ ]?([0-9]+\\*)?[xX](\\^[0-9]+)?)[ ]?([+-][ "
             "]?([0-9]+\\*)?[xX](\\^[0-9]+)?)+[ ]?");

  QValidator *equationValidaor = new QRegExpValidator(rx, 0);
  ui->equLine->setValidator(
      equationValidaor); // Assign the RegExp equation validator to the equation
                         // input field

  connect(ui->equLine, SIGNAL(inputRejected()), this, SLOT(invalidEquation()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_plotButton_clicked() {
  // Taking the equation, mininum value of x, maximum value of x from their
  // fields and store them
  QString equation = ui->equLine->text();
  float min_x = ui->minBox->value(), max_x = ui->maxBox->value();

  // As part of inputs validation functionality
  // here we pop up an information message state that the min_value must be
  // greater than the max_value if the user do the opposite
  if (min_x >= max_x) {
    QMessageBox msg;
    msg.information(0, "Function Plotter",
                    "Invalid Input.\nThe minimum value of x must be less than "
                    "or equal the maximum value of x.");
    return;
  }

  // Declare FunctionEvaluator object to evaluate the user provided equation
  FunctionEvaluator equ;
  equ.setEquation(equation);
  equ.setMinX(min_x);
  equ.setMaxX(max_x);

  series->append(
      equ.evaluatEquation()); // Pass the List of points (x,y) from
                              // evaluateEquation series to the chart series

  chart->legend()->hide(); // Hide the chart legend as we draw just one line (no
                           // need for legend here)
  chart->addSeries(series); // Pass the points series to the chart
  chart->createDefaultAxes();
  chart->setTitle("Y = " +
                  equation); // Set the chart title to the plotted equation
}

// Input: N/A
// Output: N/A
// on_release SLOT clears the chart series which hold the previous plotted
// points to be able to draw another equation when plot button clicked again
void MainWindow::on_plotButton_released() {
  chart->removeSeries(series);
  series->clear();
}

// Input: N/A
// Output: N/A
// invalidEquation SLOT pop up a message indicates a unvalid/unspported symbols
// found in the input equation.
void MainWindow::invalidEquation() {
  QMessageBox msg;
  msg.information(0, "Function Plotter",
                  "Invalid Equation.\nAny function's term should be "
                  "constructed as following\n"
                  "(sign  magnitude * x or X ^ power value).\nex: -2*X^4");
  return;
}
