//
// Created by cassius on 2023/10/23.
//


#include "dialog.h"


Dialog::Dialog(QWidget *parent) :
        QDialog(parent){
    resize(400, 270);

    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(QRect(70, 120, 260, 40));

    QFont font;
    font.setFamilies({QString::fromUtf8("宋体")});
    font.setPointSize(14);
    lineEdit->setFont(font);
    lineEdit->setText(QString());

    label = new QLabel(this);
    label->setGeometry(QRect(90,60,260,40));
    label->setFont(font);
    label->setText("请输入地点");

    btn = new QPushButton(this);
    btn->setGeometry(QRect(150,200,90,25));
    btn->setFont(font);
    btn->setText("确定");

    setWindowTitle("查找");

    connect(btn,&QPushButton::clicked,this, &Dialog::onPushBtn_clicked);

}

Dialog::~Dialog() {
    delete lineEdit;
    delete label;
    delete btn;
}

void Dialog::onPushBtn_clicked() {
    pointName = lineEdit->text();
    close();
}