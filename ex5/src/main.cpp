//
// Created by cassius on 2023/10/23.
//
#include "mainwindow.h"
#include <QApplication>
//#define _DEBUG
int main(int argc, char *argv[]){
#ifndef _DEBUG
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
#else
    BusMap bm("../resources/stops.txt", "../resources/lines.txt", "../resources/Organization.txt");
    bm.showStopsAndLines();
#endif

}