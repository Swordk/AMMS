/////////////////////////////////////////////////////////////////////////﻿
///AMMSAppWindow.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include <Qt>
#include <QStringList>
#include <QApplication>
#include <QProcess>
#include <QSplitter>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QListWidgetItem>

#include "AMMSAppWindow.h"
#include "Config.h"
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
        QSize qsize;
        qsize.setWidth(CFG()->nMovieFrameWidth());
        qsize.setHeight(CFG()->nMovieFrameHeight());
        m_pcMovieWall->Init(qsize);

        this->setCentralWidget(pcMainSplitter);
        this->showMaximized();

        auto mapActors2Sn = MDB()->Actors2Sn();
        m_pcActorsList->SetActors(mapActors2Sn);

        connect(m_pcActorsList, SIGNAL(signalActorSelected(QString)), this, SLOT(slotActorSelected(QString)));
        connect(m_pcMovieWall, SIGNAL(signalItemSelected(QString)), this, SLOT(slotMovieSelected(QString)));
    }

    void CAMMSAppWindow::slotActorSelected(QString qstrActor)
    {
        std::string strActor = qstrActor.toStdString();
        auto setSn = MDB()->Actors2Sn(strActor);
        if (setSn.empty())
            return;
        m_pcMovieWall->clear();
        QString qstrMovieDir = (CFG()->strMoviePath() + "\\").c_str();
        for (auto item : setSn) {
            QString qstr = item.c_str();
            QStringList qlist = qstr.split('-');
            if (qlist.length() != 2)
                continue;
            QString qstrPic = qstrMovieDir + qlist[0] + "\\" + qstr + "\\" + qstr + ".jpg";
            // auto itMovie = MDB()->Movies(qstr.toStdString());
            // if (itMovie.count("date"))
            //     qstr += ("     " + *(itMovie.at("date").begin())).c_str();
            QPixmap pix(qstrPic);
            QIcon ic(pix);
            QListWidgetItem* item = new QListWidgetItem(ic, qstr, m_pcMovieWall);
            m_pcMovieWall->addItem(item);
        }
    }

    void CAMMSAppWindow::slotMovieSelected(QString qstrSn)
    {
        QString qstrMovieDir = (CFG()->strMoviePath() + "\\").c_str();
        QStringList qlist = qstrSn.split('-');
        if (qlist.length() != 2)
            return;
        QString qstrMoviePath = qstrMovieDir + qlist[0] + "\\" + qstrSn + "\\" ;
        QProcess p(0);
        p.start("explorer.exe", QStringList(qstrMoviePath));
        p.waitForFinished();    //等待完成
    }

    void CAMMSAppWindow::_ProcessEvent(CEventPtr& pcEvent)
    {
        // emit signalEventToSelf(CEventObject(v_pcEvent));
    }

}
