//
// Created by cassius on 2023/10/23.
//
#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}