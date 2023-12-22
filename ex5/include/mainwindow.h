//
// Created by cassius on 2023/10/23.
//

#ifndef EX5_MAINWINDOW_H
#define EX5_MAINWINDOW_H

#include <QMainWindow>
#include "BusMap.h"
#include "Point.h"
#include "dialog.h"
#include "mywidget.h"
#include <QMouseEvent>
#include <QString>
#include <string>
#include <QPoint>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QCheckBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QMessageBox>
#include <QToolTip>

class MainWindow : public QMainWindow {
Q_OBJECT
private:
    BusMap *bp;
    bool isClicked;
    bool timerKilled;
    int startPointIndex=0, endPointIndex=0;
    int* ans = nullptr;
    int timerId=0;
    QPoint startPos, endPos;
    QWidget* centralWidget;
    QFrame *mapFrame;
    QCheckBox *nearestCheckBox;
    QCheckBox *leastCheckBox;
    QMenuBar *menuBar;
    MyWidget ** mywidgets;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void findPointByName();
    ~MainWindow() override;

private slots:
    void onNearest_changed();
    void onLeast_changed();

private:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
};


#endif //EX5_MAINWINDOW_H
