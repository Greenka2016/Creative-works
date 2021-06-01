#ifndef QCALCULATORUI_H
#define QCALCULATORUI_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include "QCalculatorDec.h"

class QCalculatorUI : public QWidget
{
    Q_OBJECT

private:
    QCalculatorDec  mDec;
    QLineEdit  *mline;              
    QPushButton *mbuton[20];       
    QCalculatorUI();
    bool construct();

private slots:
    void handler_clicked();         

public:
    int  MatchingBoth(QString &str1,const char *str2);         
    int  LastMatchingBoth(QString &str1,const char *str2);     
    static QCalculatorUI* NewIntance();    
    void show();
};
#endif // QCALCULATORUI_H
