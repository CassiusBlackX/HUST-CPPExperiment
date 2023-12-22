//
// Created by cassius on 2023/12/22.
//

#ifndef EX5_MYWIDGET_H
#define EX5_MYWIDGET_H
#include <QWidget>
#include <QEvent>
#include <QString>
#include <string>
#include <QDebug>
#include <QToolTip>
#include "Point.h"

class MyWidget : public QWidget {
Q_OBJECT

public:
    MyWidget(Point* p, QWidget* parent = nullptr)
            : QWidget(parent)
    {
        xPosition = p->getPosition().first;
        yPosition = p->getPosition().second;
        int index = p->getIndex();
        std::string index_string = "index: ";
        index_string += std::to_string(index);
        index_qstring = QString::fromStdString(index_string);
        setAttribute(Qt::WA_TranslucentBackground);
        setGeometry(xPosition, yPosition, 6, 6);  // 设置初始位置和大小
    }

protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    int xPosition;
    int yPosition;
    QString index_qstring;
};




#endif //EX5_MYWIDGET_H
