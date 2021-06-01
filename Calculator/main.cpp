#include <QtGui>
#include "QCalculatorUI.h"
#include "QCalculatorDec.h"
int main(int argc, char* argv[])
{
    /*Set font to GBK*/
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);

    QApplication app(argc,argv);
    QCalculatorUI* ui = QCalculatorUI::NewIntance();
    if(ui==NULL)
        return false;

    ui->show();
    return app.exec();
}
