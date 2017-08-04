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
#include <QTableWidget>

#include "AMMSAppWindow.h"
#include "Config.h"
#include "EventObject.h"
#include "MDataBase.h"
#include "PicCache.h"

namespace amms {

    void CAMMSAppWindow::Init()
    {
        // UI
        QSplitter* pcMainSplitter = new QSplitter(Qt::Horizontal, this);
        pcMainSplitter->setHandleWidth(1);
        pcMainSplitter->setStyleSheet("QSplitter::handle { background-color: lightgray }"); //设置分界线的样式

        QTabWidget* pcTabWidget = new QTabWidget(pcMainSplitter);

        int nTabWidgetWidth = 0;
        m_pcActorsList = new CActorsListWidget(this);
        m_pcActorsList->Init();
        int nWidth = m_pcActorsList->GetTotalWidth() + 30;
        nTabWidgetWidth = std::max(nTabWidgetWidth, nWidth);
        // m_pcActorsList->setMaximumWidth(nWidth);
        pcTabWidget->addTab(m_pcActorsList, QStringLiteral("演员"));

        m_pcSeriesList = new CCommonContentListWidget(this);
        m_pcSeriesList->Init(QStringLiteral("系列").toStdString());
        nWidth = m_pcSeriesList->GetTotalWidth() + 30;
        nTabWidgetWidth = std::max(nTabWidgetWidth, nWidth);
        // m_pcSeriesList->setMaximumWidth(nWidth);
        pcTabWidget->addTab(m_pcSeriesList, QStringLiteral("系列"));

        m_pcGenresList = new CCommonContentListWidget(this);
        m_pcGenresList->Init(QStringLiteral("类别").toStdString());
        nWidth = m_pcGenresList->GetTotalWidth() + 30;
        nTabWidgetWidth = std::max(nTabWidgetWidth, nWidth);
        // m_pcGenresList->setMaximumWidth(nWidth);
        pcTabWidget->addTab(m_pcGenresList, QStringLiteral("类别"));

        m_pcSnList = new CCommonContentListWidget(this);
        m_pcSnList->Init(QStringLiteral("番号").toStdString());
        nWidth = m_pcSnList->GetTotalWidth() + 30;
        nTabWidgetWidth = std::max(nTabWidgetWidth, nWidth);
        // m_pcSnList->setMaximumWidth(nWidth);
        pcTabWidget->addTab(m_pcSnList, QStringLiteral("番号"));

        pcTabWidget->setMaximumWidth(nTabWidgetWidth);

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


        // Datas
        auto mapActors2Sn = MDB()->Actors2Sn();
        m_pcActorsList->SetActors(mapActors2Sn);

        auto mapSereis2Sn = MDB()->Series2Sn();
        std::map<std::string, int> mapSereis2Count;
        for (auto& item : mapSereis2Sn)
            mapSereis2Count[item.first] = item.second.size();
        m_pcSeriesList->SetContents(mapSereis2Count);

        auto mapGenres2Sn = MDB()->Genres2Sn();
        std::map<std::string, int> mapGenres2Count;
        for (auto& item : mapGenres2Sn)
            mapGenres2Count[item.first] = item.second.size();
        m_pcGenresList->SetContents(mapGenres2Count);


        m_pcMovieInfoWindow = new CMovieInfoWindow(this);
        m_pcMovieInfoWindow->Init();
        m_pcMovieInfoWindow->hide();
        connect(m_pcActorsList, SIGNAL(signalActorSelected(QString)), this, SLOT(slotActorSelected(QString)));
        connect(m_pcActorsList, SIGNAL(signalActorSelected(QString)), m_pcActorInfoWidget, SLOT(slotSetlActor(QString)));

        connect(m_pcSeriesList, SIGNAL(signalContentSelected(QString)), this, SLOT(slotSeriesSelected(QString)));
        connect(m_pcGenresList, SIGNAL(signalContentSelected(QString)), this, SLOT(slotGenresSelected(QString)));
        connect(m_pcSnList, SIGNAL(signalContentSelected(QString)), this, SLOT(slotSnSelected(QString)));

        connect(m_pcMovieWall, SIGNAL(signalItemSelected(QString)), this, SLOT(slotMovieSelected(QString)));

        connect(this, SIGNAL(signalEventToSelf(CEventObject)), this, SLOT(slotEventFromSelf(CEventObject)));
        connect(m_pcMovieWall, SIGNAL(signalEventToParent(CEventObject)), this, SLOT(slotEventFromChild(CEventObject)));
        connect(this, SIGNAL(signalEventToChild(CEventObject)), m_pcMovieWall, SLOT(slotEventFromParent(CEventObject)));

        RegisterEventProcesser(etRspLoadPic);

    }

    void CAMMSAppWindow::slotActorSelected(QString qstrActor)
    {
        // m_mapFile2Item.clear();
        std::string strActor = qstrActor.toStdString();
        auto setMovies = MDB()->Actors2Sn(strActor);
        m_pcMovieWall->SetMovies(setMovies);
        // Movies2MovieWall(setMovies);
    }

    void CAMMSAppWindow::slotSeriesSelected(QString qstrSeries)
    {
        // m_mapFile2Item.clear();
        auto& setMovies = MDB()->Series2Sn(qstrSeries.toStdString());
        m_pcMovieWall->SetMovies(setMovies);
        // Movies2MovieWall(setMovies);
    }

    void CAMMSAppWindow::slotGenresSelected(QString qstrGenres)
    {
        // m_mapFile2Item.clear();
        auto& setMovies = MDB()->Genres2Sn(qstrGenres.toStdString());
        m_pcMovieWall->SetMovies(setMovies);
        // Movies2MovieWall(setMovies);
    }

    void CAMMSAppWindow::slotSnSelected(QString qstrSn)
    {

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
                std::string strFileName = pcRspEvent->m_strFileName;
                emit signalEventToChild(CEventObject(CEventPtr(new CLoadPicRspEvent(strFileName, true))));
            }
            break;
        }
        default:
            break;
        }
    }

    void CAMMSAppWindow::slotEventFromChild(CEventObject objEvent)
    {
        CEventPtr pcEvent = objEvent.GetEvent();
        switch (pcEvent->Type()) {
        case etReqLoadPic: {
            CLoadPicReqEvent* pcReqEvent = (CLoadPicReqEvent*)(pcEvent.get());
            PostEvent(CEventPtr(new CLoadPicReqEvent(pcReqEvent->m_strFileName)));
            break;
        }
        }
    }

    // void CAMMSAppWindow::Movies2MovieWall(const std::set<std::string>& setMovies)
    // {
    //     if (setMovies.empty())
    //         return;
    //     m_pcMovieWall->clear();
    //     QString qstrMovieDir = (CFG()->MoviePath() + "\\").c_str();
    //     for (auto item : setMovies) {
    //         QString qstr = item.c_str();
    //         QStringList qlist = qstr.split('-');
    //         if (qlist.length() != 2)
    //             continue;
    //         QString qstrPic = qstrMovieDir + qlist[0] + "\\" + qstr + "\\" + qstr + ".jpg";
    //         string strPic = qstrPic.toStdString();
    //         // auto itMovie = MDB()->Movies(qstr.toStdString());
    //         // if (itMovie.count("date"))
    //         //     qstr += ("     " + *(itMovie.at("date").begin())).c_str();
    //         QPixmap pix("amms.png");
    //         if (PicCacheInst()->HasPixmap(strPic))
    //             PicCacheInst()->GetPixmap(strPic, pix);
    //         else {
    //             // pix.
    //             PostEvent(CEventPtr(new CLoadPicReqEvent(strPic)));
    //         }
    //         QIcon ic(pix);
    //         QListWidgetItem* item = new QListWidgetItem(ic, qstr, m_pcMovieWall);
    //         m_mapFile2Item[strPic] = item;
    //         m_pcMovieWall->addItem(item);
    //     }
    // }
}
