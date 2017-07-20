/////////////////////////////////////////////////////////////////////////﻿
///AMMSAppWindow.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include <Qt>
#include <QStringList>
#include <QApplication>
#include <QProcess>
#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidgetItem>

#include "AMMSAppWindow.h"
#include "Config.h"
#include "EventObject.h"
#include "MDataBase.h"
#include "PicCache.h"

namespace amms {

    void CAMMSAppWindow::Init()
    {
        QSplitter* pcMainSplitter = new QSplitter(Qt::Horizontal, this);
        pcMainSplitter->setHandleWidth(1);
        pcMainSplitter->setStyleSheet("QSplitter::handle { background-color: lightgray }"); //设置分界线的样式
        m_pcActorsList = new CActorsListWidget(pcMainSplitter);
        m_pcActorsList->Init();
        m_pcActorsList->setMaximumWidth(m_pcActorsList->GetTotalWidth() + 30);

        QWidget* pcWidget = new QWidget(pcMainSplitter);
        pcWidget->setStyleSheet("QWidget { border: 0px } ");
        QVBoxLayout* pcLayout = new QVBoxLayout(pcWidget);
        pcWidget->setLayout(pcLayout);

        m_pcActorInfoWidget = new CActorInfoWidget(pcWidget);
        m_pcActorInfoWidget->Init();

        m_pcMovieWall = new CMovieWallWidget(pcWidget);
        QSize qsize;
        qsize.setWidth(CFG()->MovieFrameWidth());
        qsize.setHeight(CFG()->MovieFrameHeight());
        m_pcMovieWall->Init(qsize);

        pcLayout->addWidget(m_pcActorInfoWidget);
        pcLayout->addWidget(m_pcMovieWall);

        this->setCentralWidget(pcMainSplitter);
        this->showMaximized();

        auto mapActors2Sn = MDB()->Actors2Sn();
        m_pcActorsList->SetActors(mapActors2Sn);

        m_pcMovieInfoWindow = new CMovieInfoWindow(this);
        m_pcMovieInfoWindow->Init();
        m_pcMovieInfoWindow->hide();
        connect(m_pcActorsList, SIGNAL(signalActorSelected(QString)), this, SLOT(slotActorSelected(QString)));
        connect(m_pcActorsList, SIGNAL(signalActorSelected(QString)), m_pcActorInfoWidget, SLOT(slotSetlActor(QString)));
        connect(m_pcMovieWall, SIGNAL(signalItemSelected(QString)), this, SLOT(slotMovieSelected(QString)));

        connect(this, SIGNAL(signalEventToSelf(CEventObject)), this, SLOT(slotEventFromSelf(CEventObject)));
        RegisterEventProcesser(etRspLoadPic);

    }

    void CAMMSAppWindow::slotActorSelected(QString qstrActor)
    {
        m_mapFile2Item.clear();
        std::string strActor = qstrActor.toStdString();
        auto setSn = MDB()->Actors2Sn(strActor);
        if (setSn.empty())
            return;
        m_pcMovieWall->clear();
        QString qstrMovieDir = (CFG()->MoviePath() + "\\").c_str();
        for (auto item : setSn) {
            QString qstr = item.c_str();
            QStringList qlist = qstr.split('-');
            if (qlist.length() != 2)
                continue;
            QString qstrPic = qstrMovieDir + qlist[0] + "\\" + qstr + "\\" + qstr + ".jpg";
            string strPic = qstrPic.toStdString();
            // auto itMovie = MDB()->Movies(qstr.toStdString());
            // if (itMovie.count("date"))
            //     qstr += ("     " + *(itMovie.at("date").begin())).c_str();
            QPixmap pix("amms.png");
            if (PicCacheInst()->HasPixmap(strPic))
                PicCacheInst()->GetPixmap(strPic, pix);
            else {
                // pix.
                PostEvent(CEventPtr(new CLoadPicReqEvent(strPic)));
            }
            QIcon ic(pix);
            QListWidgetItem* item = new QListWidgetItem(ic, qstr, m_pcMovieWall);
            m_mapFile2Item[strPic] = item;
            m_pcMovieWall->addItem(item);
        }
    }

    void CAMMSAppWindow::slotMovieSelected(QString qstrSn)
    {
        m_pcMovieInfoWindow->SetSn(qstrSn);
        m_pcMovieInfoWindow->show();
        // QString qstrMovieDir = (CFG()->strMoviePath() + "\\").c_str();
        // QStringList qlist = qstrSn.split('-');
        // if (qlist.length() != 2)
        //     return;
        // QString qstrMoviePath = qstrMovieDir + qlist[0] + "\\" + qstrSn + "\\" ;
        // QProcess p(0);
        // p.start("explorer.exe", QStringList(qstrMoviePath));
        // p.waitForFinished();    //等待完成
    }

    void CAMMSAppWindow::_ProcessEvent(CEventPtr& pcEvent)
    {
        emit signalEventToSelf(CEventObject(pcEvent));
    }

    void CAMMSAppWindow::slotEventFromSelf(CEventObject objEvent)
    {
        CEventPtr pcEvent = objEvent.GetEvent();
        switch (pcEvent->Type()) {
        case etRspLoadPic: {
            CLoadPicRspEvent* pcRspEvent = (CLoadPicRspEvent*)(pcEvent.get());
            if (pcRspEvent && pcRspEvent->m_bSuccess) {
                string strFileName = pcRspEvent->m_strFileName;
                if (m_mapFile2Item.count(strFileName)) {
                    QPixmap pix;
                    PicCacheInst()->GetPixmap(strFileName, pix);
                    m_mapFile2Item[strFileName]->setIcon(QIcon(pix));
                    m_mapFile2Item[strFileName]->setHidden(true);
                    m_mapFile2Item[strFileName]->setHidden(false);

                }
            }
            break;
        }
        }
    }
}
