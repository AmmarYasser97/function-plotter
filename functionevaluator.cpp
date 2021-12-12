#include "functionevaluator.h"

// Input: Equation to be plotted
// Output: N/A
// Set the equation private variable by this public method, after checking it's
// not an empty string
void FunctionEvaluator::setEquation(QString equation) {
  if (equation == "")
    return;
  this->equation = equation;
}

// Input:
// Output: N/A
// Set the minimum value of X which can be in range (-99.00,99.00)
void FunctionEvaluator::setMinX(float number) { this->minimumX = number; }

// Input:
// Output: N/A
// Set the maximum value of X which can be in range (-99.00,99.00)
void FunctionEvaluator::setMaxX(float number) { this->maximumX = number; }

// Input: Equation to be plotted
// Output: List of mathimatical terms
// Depend on the input equation, this method split the equation to a list of
// strings relying on two separators (+ or -)
QStringList FunctionEvaluator::splitTerms(QString equation) {
  QRegExp delimiter("[+-]");
  QStringList terms = equation.split(delimiter, QString::SkipEmptyParts);

  return terms;
}

// Input: Equation to be plotted
// Output: Vector of signs (+ or -)
// Catch every sign and push it to a list
QVector<QChar> FunctionEvaluator::splitSigns(QString equation) {
  QVector<QChar> signs;

  if (!(equation[0] == '+' || equation[0] == '-')) {
    signs.push_back('+');
  }

  for (int i = 0; i < equation.length(); i++) {
    if (equation[i] == '+' || equation[i] == '-') {
      signs.push_back(equation[i]);
    }
  }

  return signs;
}

// Input: Minimum value of X, Maximum value of X, step between two X values
// Output: Vector of floats holding the x values
// Generate the values of X starting from min value to max value based on the
// step, with default step value = 0.1
QVector<float> FunctionEvaluator::rangeOfX(float min_x, float max_x,
                                           float step) {
  QVector<float> values;
  for (float i = min_x; i <= max_x; i += step) {
    values.push_back(i);
  }

  return values;
}

// Input: Term, its sign, X value
// Output: Float value of the evaluated term
// Evaluate a given term of the input equation for a given value of X and return
// the result
float FunctionEvaluator::evaluatTerm(QString term, QChar sign, float x_value) {
  float magnitude = 0, power = 0;
  float result;

  if (!term.contains('*'))
    magnitude = 1;
  else
    magnitude = term.left(term.indexOf("*")).toFloat();

  if (!term.contains('^'))
    power = 1;
  else
    power = term.mid(term.indexOf("^") + 1).toFloat();

  magnitude = (sign == '-') ? magnitude * -1 : magnitude;
  result = magnitude * pow(x_value, power);

  return result;
}

// Input: N/A
// Output: List of points (X, Y)
// Get the Y value of the input equation for every value of X and construct (x,
// y) points to plot them
QList<QPointF> FunctionEvaluator::evaluatEquation() {
  QList<QPointF> points;
  QPointF point;

  QStringList terms = splitTerms(equation);
  QVector<QChar> signs = splitSigns(equation);
  QVector<float> values = rangeOfX(minimumX, maximumX, X_STEP);

  for (float x_value : values) {
    float y_value = 0;
    for (int j = 0; j < terms.length(); j++) {
      y_value += evaluatTerm(terms[j], signs[j], x_value);
    }
    points.push_back(QPointF(x_value, y_value));
  }
  return points;
}

// Input: N/A
// Output: N/A
// Class constructor
FunctionEvaluator::FunctionEvaluator() {}
