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

#include "AMMSAppWindow.h"
#include "EventObject.h"
#include "MDataBase.h"

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

        auto mapActors2Sn = MDB()->Actors2Sn();
        m_pcActorsList->SetActors(mapActors2Sn);

        connect(m_pcActorsList, SIGNAL(signalActorSelected(QString)), this, SLOT(slotActorSelected(QString)));
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
            m_pcMovieWall->AddItem(qstr, "d:/2.jpg");
        }
    }

    void CAMMSAppWindow::slotActorSelected(QString qstrActor)
    {
        std::string strActor = qstrActor.toStdString();
        auto setSn = MDB()->Actors2Sn(strActor);
        if (setSn.empty())
            return;
        m_pcMovieWall->clear();
        for (auto item : setSn) {
            QString qstr = item.c_str();
            QPixmap pix("d:/2.jpg");
            QIcon ic(pix);
            QListWidgetItem* item = new QListWidgetItem(ic, qstr, m_pcMovieWall);
            m_pcMovieWall->addItem(item);
        }
    }


    void CAMMSAppWindow::_ProcessEvent(CEventPtr& pcEvent)
    {
        // emit signalEventToSelf(CEventObject(v_pcEvent));
    }

}
