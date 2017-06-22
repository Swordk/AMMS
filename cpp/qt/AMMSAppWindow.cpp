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
#include <QListWidgetItem>
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

        m_pcMovieWall = new CMovieWallWidget(pcMainSplitter);
        m_pcMovieWall->Init(QSize(240, 350));

        this->setCentralWidget(pcMainSplitter);
        this->showMaximized();
    }

    void CAMMSAppWindow::resizeEvent(QResizeEvent* pcEvent)
    {
        QSize widgetNewSize = pcEvent->size();
        int jjj=0;
    }

    void CAMMSAppWindow::mouseReleaseEvent(QMouseEvent* pcEvent)
    {
        QVector<QWidget*> vecs;
        for (int n=0; n < 16; ++n) {
            QString qstr = "This is " + QString::number(n);
            QPixmap pix("d:/2.jpg");
            // QIcon ic = QIcon(pix.scaled(212, 300));
            QIcon ic(pix);
            QListWidgetItem* item = new QListWidgetItem(ic, qstr, m_pcMovieWall);
            m_pcMovieWall->addItem(item);
        }
    }

    void CAMMSAppWindow::_ProcessEvent(CEventPtr& pcEvent)
    {

    }

}
