//
// Created by cassius on 2023/12/22.
//

#include "mywidget.h"

void MyWidget::enterEvent(QEnterEvent *event) {
    QToolTip::showText(mapToGlobal(QPoint(0, 0)), index_qstring);
}

void MyWidget::leaveEvent(QEvent *event) {
    if(event->type() == QEvent::Leave){
        QToolTip::hideText();
    }
}
