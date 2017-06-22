/////////////////////////////////////////////////////////////////////////﻿
///AMMSAppWindow.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include <Qt>
#include <QApplication>
#include <QSplitter>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "EventObject.h"
#include "AMMSAppWindow.h"

namespace amms {

    void CAMMSAppWindow::Init()
    {
        QSplitter* pcMainSplitter = new QSplitter(Qt::Horizontal, this);
        pcMainSplitter->setHandleWidth(1);
        pcMainSplitter->setStyleSheet("QSplitter::handle { background-color: lightgray }"); //设置分界线的样式
        QLabel* lab1 = new QLabel(pcMainSplitter);
        QLabel* lab2 = new QLabel(pcMainSplitter);
        lab1->setText("123");
        lab2->setText("456");
        pcMainSplitter->setStretchFactor(0, 1);
        pcMainSplitter->setStretchFactor(1, 4);

        this->setCentralWidget(pcMainSplitter);
        this->showMaximized();
    }


    void CAMMSAppWindow::_ProcessEvent(CEventPtr& pcEvent)
    {

    }

}
