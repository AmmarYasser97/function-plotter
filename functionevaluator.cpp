#include "functionevaluator.h"

void FunctionEvaluator:: setEquation(QString equation) {
    if (equation == "")
        return;
    this->equation = equation;
}

void FunctionEvaluator:: setMinX(float number) {
    this->minimumX = number;
}

void FunctionEvaluator:: setMaxX(float number) {

    this->maximumX = number;
}

QStringList FunctionEvaluator::splitTerms (QString equation) {
    QRegExp delimiter("[+-]");
    QStringList terms = equation.split(delimiter, QString::SkipEmptyParts) ;

    return terms;
}

QVector<QChar> FunctionEvaluator::splitSigns (QString equation) {
    QVector<QChar> signs;

    if(!(equation[0] == '+' || equation[0] == '-')) {
        signs.push_back('+');
    }

    for(int i=0; i < equation.length(); i++){
        if(equation[i] == '+' || equation[i] == '-') {
            signs.push_back(equation[i]);
        }
    }

    return signs;
}

QVector <float> FunctionEvaluator:: rangeOfX (float min_x, float max_x) {
    QVector<float> values;
    for(float i = min_x ; i <= max_x ; i++) {
        values.push_back(i);
    }

    return values;
}

float FunctionEvaluator::evaluatTerm (QString term, QChar sign, float x_value) {
    float magnitude = 0, power = 0;
    float result;

    if(!term.contains('*'))
        magnitude = 1;
    else
        magnitude = term.left(term.indexOf("*")).toFloat();

    magnitude = (sign == '-') ? magnitude * -1 : magnitude;
    power = term.right(term.indexOf("^")).toFloat();

    result = magnitude * pow(x_value, power);

    return result;
}

QList<QPointF> FunctionEvaluator::evaluatEquation () {
    QList<QPointF> points;
    QPointF point;

    QStringList terms = splitTerms(equation);
    QVector <QChar> signs = splitSigns(equation);
    QVector <float> values = rangeOfX (minimumX, maximumX);

    for(float x_value : values) {
        float y_value = 0;
        for(int j = 0; j < terms.length(); j++) {
            y_value += evaluatTerm(terms[j], signs[j], x_value);
        }
        points.push_back(QPointF(x_value, y_value));
    }
    return points;
}

FunctionEvaluator::FunctionEvaluator()  {}
