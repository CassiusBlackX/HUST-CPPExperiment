//
// Created by cassius on 2023/10/23.
//

#ifndef EX5_DIALOG_H
#define EX5_DIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

class Dialog : public QDialog {
Q_OBJECT

public:
    QString pointName;
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private slots:
    void onPushBtn_clicked();

private:
    QLineEdit *lineEdit;
    QLabel *label;
    QPushButton *btn;
};


#endif //EX5_DIALOG_H
