//
// Created by cassius on 2023/10/23.
//

// You may need to build the project (run Qt uic code generator) to get "ui_mainwindow.h" resolved

#include "mainwindow.h"
//#define DEBUG_MODE
#ifdef DEBUG_MODE
#include <QDebug>
#endif

int matchString(const std::string& a, const std::string& b){
    int cnt = 0;
    for(int i=0;i<b.length();i+=3){
        for(int j=0;j<a.length();j+=3){
            bool flag = true;
            if(i+2<b.length() && j+2<a.length()){
                for(int k=0;k<3;k++){
                    if(a[j+k] != b[i+k]){
                        flag = false;
                        break;
                    }
                }
            }
            if(flag){
                cnt++;
                break;
            }
        }
    }
    return cnt;
}

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent) {
    // ui的设计
    // 设置窗口的大小和标题
    setGeometry(0,0,1020,618);
    setWindowTitle("华中科技大学周边导航系统");

    // 创建主窗口的中央部件
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建垂直布局
    auto *verticalLayout = new QVBoxLayout(centralWidget);

    // 创建地图区域并添加到布局
    mapFrame = new QFrame(centralWidget);
    verticalLayout->addWidget(mapFrame);

    // 创建水平布局
    auto *horizontalLayout = new QHBoxLayout();

    horizontalLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));


    // 创建“距离最近”的复选框
    nearestCheckBox = new QCheckBox("距离最近", centralWidget);
    nearestCheckBox->setFont(QFont("Arial", 15));
    horizontalLayout->addWidget(nearestCheckBox);

    horizontalLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // 创建“换乘次数最少”的复选框
    leastCheckBox = new QCheckBox("换乘次数最少", centralWidget);
    leastCheckBox->setFont(QFont("Arial", 15));
    horizontalLayout->addWidget(leastCheckBox);

    // 向水平布局中添加部件
    horizontalLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // 将水平布局添加到垂直布局
    verticalLayout->addLayout(horizontalLayout);

    // 创建菜单栏
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // 创建“文件”菜单
    QMenu *fileMenu = menuBar->addMenu("文件");
    auto *stopAction = new QAction("stops.txt", this);
    auto *linesAction = new QAction("lines.txt", this);
    auto *orgAction = new QAction("Organization.txt", this);
    fileMenu->addAction(stopAction);
    fileMenu->addAction(linesAction);
    fileMenu->addAction(orgAction);

    // 创建“说明”菜单
    QMenu *helpMenu = menuBar->addMenu("说明");
    auto *action1 = new QAction("首次单机左键选定起点", this);
    auto *action2 = new QAction("再次单机左键选定终点", this);
    auto *action3 = new QAction("查找地点 R", this);
    auto *action4 = new QAction("蓝色代表起点", this);
    auto *action5 = new QAction("红色代表终点", this);
    helpMenu->addAction(action1);
    helpMenu->addAction(action2);
    helpMenu->addAction(action3);
    helpMenu->addAction(action4);
    helpMenu->addAction(action5);

    // 创建”查找“菜单
    QMenu *findMenu = menuBar->addMenu("查找");
    auto *findAction = new QAction("查找地点 R");
    findMenu->addAction(findAction);

    // 相关成员变量的初始化
    leastCheckBox->setChecked(true);
    move(30, 20);
    startPos.setX(0);
    startPos.setY(0);
    endPos.setX(0);
    endPos.setY(0);
    isClicked = false;
    timerKilled = false;
    bp = new BusMap("../resources/stops.txt", "../resources/lines.txt", "../resources/Organization.txt");
    connect(findAction, &QAction::triggered, this, &MainWindow::findPointByName);
    connect(nearestCheckBox,&QCheckBox::clicked,this, &MainWindow::onNearest_changed);
    connect(leastCheckBox,&QCheckBox::clicked,this, &MainWindow::onLeast_changed);

    mywidgets = new MyWidget * [bp->getBusStopsNum()+1];
    for(int i=1;i<=bp->getBusStopsNum();i++){
        Point *point = bp->getBusStops()[i];
        mywidgets[i] = new MyWidget(point, this);
    }
}

MainWindow::~MainWindow() {
    delete leastCheckBox;
    delete nearestCheckBox;
    delete menuBar;
    delete mapFrame;
    delete centralWidget;
    delete ans;
    delete bp;
    leastCheckBox = nullptr;
    nearestCheckBox = nullptr;
    menuBar = nullptr;
    mapFrame = nullptr;
    centralWidget = nullptr;
    ans = nullptr;
    bp = nullptr;
    if(!timerKilled){
        killTimer(timerId);
    }
}

void MainWindow::paintEvent(QPaintEvent *event) {
    mapFrame->setFixedHeight(820);
    mapFrame->setFixedWidth(1670);
    QRect mapRect = mapFrame->frameRect();
    mapRect.translate(mapFrame->pos());
    QImage mapImage("../resources/hustMap.bmp");
    QPainter mapPainter(this);
    QPen mapPen;
    mapPainter.drawImage(mapRect, mapImage);

    // draw stop points;
    QRectF busStopsRect;
    mapPainter.setBrush(QColor(0,0,0));
    for(int i=1;i<=bp->getBusStopsNum();i++){
        Point *_p = bp->getBusStops()[i];
        busStopsRect.setTop(_p->getPosition().second+6);
        busStopsRect.setBottom(_p->getPosition().second-6);
        busStopsRect.setLeft(_p->getPosition().first-6);
        busStopsRect.setRight(_p->getPosition().first+6);
        mapPainter.drawEllipse(busStopsRect);
    }


    // draw start and end point
    if(startPos.x() != 0){
        mapPen.setWidth(1);
        mapPen.setColor(Qt::blue);
        mapPainter.setPen(mapPen);
        mapPainter.setBrush(Qt::blue);
        busStopsRect.setTop(startPos.y()+6);
        busStopsRect.setBottom(startPos.y()-6);
        busStopsRect.setLeft(startPos.x()-6);
        busStopsRect.setRight(startPos.x()+6);
        mapPainter.drawEllipse(busStopsRect);
    }
    if(endPos.x()!=0){
        mapPen.setColor(Qt::red);
        mapPainter.setBrush(Qt::red);
        mapPainter.setPen(mapPen);
        busStopsRect.setTop(endPos.y()+6);
        busStopsRect.setBottom(endPos.y()-6);
        busStopsRect.setLeft(endPos.x()-6);
        busStopsRect.setRight(endPos.x()+6);
        mapPainter.drawEllipse(busStopsRect);
    }

    // draw bus lines
    mapPainter.setBrush(Qt::NoBrush);
    mapPen.setWidth(3);
    mapPen.setColor(Qt::green);
    mapPen.setStyle(Qt::DotLine);
    mapPainter.setPen(mapPen);
    for(int i=1;i<=bp->getBusLinesNum();i++){
        for(int j=1;j<bp->getEachBusLineNum()[i];j++){
            Point *p1 = bp->getBusStops()[bp->getBusLines()[i][j]];
            Point *p2 = bp->getBusStops()[bp->getBusLines()[i][j+1]];
            mapPainter.drawLine(p1->getPosition().first,p1->getPosition().second,
                                p2->getPosition().first,p2->getPosition().second);
        }
    }

    // draw path
    int temp = endPointIndex;
    if(!ans || temp == 0){
        return;
    }
    mapPen.setWidth(3);
    mapPen.setColor(Qt::blue);
    mapPen.setStyle(Qt::SolidLine);
    mapPainter.setPen(mapPen);
    mapPainter.setBrush(Qt::NoBrush);
    mapPainter.drawLine(endPos.x(), endPos.y(), bp->getBusStops()[temp]->getPosition().first,
                        bp->getBusStops()[temp]->getPosition().second);
    while(ans[temp] != 0){
        mapPainter.drawLine(bp->getBusStops()[temp]->getPosition().first,
                            bp->getBusStops()[temp]->getPosition().second,
                            bp->getBusStops()[ans[temp]]->getPosition().first,
                            bp->getBusStops()[ans[temp]]->getPosition().second);
        temp = ans[temp];
    }
    mapPainter.drawLine(startPos.x(), startPos.y(), bp->getBusStops()[temp]->getPosition().first,
                        bp->getBusStops()[temp]->getPosition().second);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QPoint mousePoint = event->pos();
    Point mousePointTemp;
    mousePointTemp.setPosition(mousePoint.x(),mousePoint.y());
    double minDistance = 999999.9999;
    for(int i=1;i<=bp->getBusStopsNum();i++){
        double temp = calDistance(mousePointTemp,*bp->getBusStops()[i]);
        if(temp<minDistance){
            minDistance = temp;
            if(!isClicked){
                startPointIndex = i;
            }
            else{
                endPointIndex = i;
            }
        }
    }
    if(!isClicked){
        isClicked = true;
        startPos = event->pos();
        endPos.setX(0);
        endPos.setY(0);
        repaint(centralWidget->contentsRect());
        if(!timerKilled){
            killTimer(timerId);
            timerKilled = true;
        }
    }
    else{
        endPos = event->pos();
        if(nearestCheckBox->isChecked()){
            ans = bp->findNearestPath(startPointIndex, endPointIndex);
        }
        else{
            ans = bp->findLeastStations(startPointIndex, endPointIndex);
        }
        repaint(centralWidget->contentsRect());
#ifdef DEBUG_MODE
        timerId = startTimer(1000);
#endif
#ifndef DEBUG_MODE
        timerId = startTimer(5000);
        timerKilled = false;
#endif
        startPointIndex = 0;
        endPointIndex = 0;
        startPos.setX(0);
        startPos.setY(0);
        endPos.setX(0);
        endPos.setY(0);
        isClicked = false;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_R){
        findPointByName();
    }
}

void MainWindow::findPointByName() {
    auto *findPointDialog = new Dialog(this);
    findPointDialog->show();
    findPointDialog->exec();
    std::string pointName = findPointDialog->pointName.toStdString();
    if(pointName.empty()){
        // if it is an empty input, then we will just close the dialog
        delete findPointDialog;
        return;
    }
    else{
        if(!isClicked){
            int maxCnt=0;
            int ansIndex=0;
            for(int i=1;i<=bp->getOrgNum();i++){
                if(matchString(bp->getOrgames()[i],pointName)>maxCnt){
                    maxCnt=matchString(bp->getOrgames()[i],pointName);
                    ansIndex=i;
                }
            }
            if(ansIndex == 0){
                // unable to find an organization's name that matches the input
                delete findPointDialog;
                findPointDialog = nullptr;
                QMessageBox messageBox(QMessageBox::Critical,"查找失败","未查找到输入的地点！",
                                       QMessageBox::Ok, this);
                messageBox.exec();
                return;
            }
            if(!timerKilled) {
                killTimer(timerId);
                timerKilled = true;
            }
            isClicked = true;
            startPos.setX(bp->getOrgPos()[ansIndex].first);
            startPos.setY(bp->getOrgPos()[ansIndex].second);
            Point startPointTmp;
            startPointTmp.setPosition(startPos.x(),startPos.y());
            double minDis = 99999.9999;
            for(int i=1;i<=bp->getBusStopsNum();i++){
                double tmp = calDistance(startPointTmp,*bp->getBusStops()[i]);
                if(tmp<minDis){
                    minDis = tmp;
                    startPointIndex = i;
                }
            }
            repaint(centralWidget->contentsRect());
        }
        else{
            int maxCnt=0;
            int ansIndex=0;
            for(int i=1;i<=bp->getOrgNum();i++){
                if(matchString(bp->getOrgames()[i],pointName)>maxCnt){
                    maxCnt=matchString(bp->getOrgames()[i],pointName);
                    ansIndex=i;
                }
            }
            if(ansIndex == 0){
                delete findPointDialog;
                findPointDialog = nullptr;
                QMessageBox messageBox(QMessageBox::Critical, "查找失败", "未查找到地点！", QMessageBox::Ok, this);
                messageBox.exec();
                return;
            }
            endPos.setX(bp->getOrgPos()[ansIndex].first);
            endPos.setY(bp->getOrgPos()[ansIndex].second);
            Point endPointTmp;
            endPointTmp.setPosition(endPos.x(), endPos.y());
            double minDis = 9999999.9999;
            for(int i=1;i<=bp->getBusStopsNum();i++){
                double tmp = calDistance(endPointTmp,*bp->getBusStops()[i]);
                if(tmp<minDis){
                    minDis = tmp;
                    endPointIndex = i;
                }
            }
            if(nearestCheckBox->isChecked()){
                ans = bp->findNearestPath(startPointIndex, endPointIndex);
            }
            else{
                ans = bp->findLeastStations(startPointIndex, endPointIndex);
            }
            repaint(centralWidget->contentsRect());
            timerId = startTimer(5000);
            timerKilled = false;
            startPointIndex = 0;
            endPointIndex = 0;
            isClicked = false;
        }
    }
    delete findPointDialog;
}

void MainWindow::timerEvent(QTimerEvent *event) {
    startPointIndex = 0;
    endPointIndex = 0;
    startPos.setX(0);
    startPos.setY(0);
    endPos.setX(0);
    endPos.setY(0);
    killTimer(timerId);
    timerKilled = true;
    update();
#ifdef DEBUG_MODE
    qDebug()<<"shit killing timerId: "<<timerId;
#endif
}

void MainWindow::onNearest_changed() {
    if(nearestCheckBox->isChecked()){
        leastCheckBox->setChecked(false);
    }
    else{
        leastCheckBox->setChecked(true);
    }
}

void MainWindow::onLeast_changed() {
    if(leastCheckBox->isChecked()){
        nearestCheckBox->setChecked(false);
    }
    else{
        nearestCheckBox->setChecked(true);
    }
}

