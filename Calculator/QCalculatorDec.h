#ifndef QCALCULATORDEC_H
#define QCALCULATORDEC_H
#include <QString>
#include <QStack>
#include <QQueue>
#include <QDebug>
class QCalculatorDec
{
private:
    QQueue<QString> Split(const QString& exp);         
    QQueue<QString> Transfer(QQueue<QString>& exp);    
    QString Calculate(QQueue<QString>& exp);           

    QString Calculate(QString& l,QString& op,QString& r );
    QString ValidNum(QString str);

public:
    QCalculatorDec();
    QString Result(const QString& exp);
};

#endif 

