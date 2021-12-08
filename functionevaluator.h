#ifndef FUNCTIONEVALUATOR_H
#define FUNCTIONEVALUATOR_H

#include <cmath>
#include <QString>
#include <QStringList>
#include <QRegExp>
#include <QVector>
#include <QChar>
#include <QList>
#include <QPointF>

class FunctionEvaluator
{
public:
    void setEquation(QString equation);
    void setMinX(float number);
    void setMaxX(float number);
    QList<QPointF> evaluatEquation ();
    FunctionEvaluator();

private:
    QString equation;
    float maximumX, minimumX;
    QStringList splitTerms (QString equation);
    QVector<QChar> splitSigns (QString equation);
    QVector <float> rangeOfX (float min_x, float max_x);
    float evaluatTerm (QString term, QChar sign, float x_value);

};

#endif // FUNCTIONEVALUATOR_H
