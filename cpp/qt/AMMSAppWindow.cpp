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
        m_pcActorsList = new CActorsListWidget(pcMainSplitter);
        m_pcActorsList->Init();
        m_pcActorsList->setMaximumWidth(m_pcActorsList->GetTotalWidth() + 30);

        QLabel* lab2 = new QLabel(pcMainSplitter);
        lab2->setText("456");

        this->setCentralWidget(pcMainSplitter);
        this->showMaximized();
    }


    void CAMMSAppWindow::_ProcessEvent(CEventPtr& pcEvent)
    {

    }

}
