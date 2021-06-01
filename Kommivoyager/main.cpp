#include "graph.h"
#include <QApplication>
#include <queue>
#include <iostream>
#include <Windows.h>
using namespace std;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Graph w;
    w.show();
    return a.exec();
}
