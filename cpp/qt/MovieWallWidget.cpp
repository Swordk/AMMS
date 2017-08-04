/////////////////////////////////////////////////////////////////////////﻿
///DynamicGridWidget
///20160919 jason wong 创建该文件
///随着窗口大小变化，可动态调整每行Widget数量的GridWidget
/////////////////////////////////////////////////////////////////////////

#include "MovieWallWidget.h"
#include <QStringList>
#include "Config.h"
#include "MDataBase.h"
#include "PicCache.h"

namespace amms {
    void CMovieWallWidget::Init(QSize frameSize)
    {
        this->setViewMode(QListView::IconMode);
        this->setIconSize(frameSize);
        this->setResizeMode(QListView::ResizeMode::Adjust);
        this->setMovement(QListView::Movement::Static);
        this->setSpacing(5);

        // 自动换行
        this->setFlow(QListView::LeftToRight);
        this->setProperty("isWrapping", QVariant(true));
        this->setWordWrap(true);

        connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotItemDoubleClicked(QListWidgetItem*)));
    }


    void CMovieWallWidget::SetMovies(const std::set<std::string>& setMovies)
    {
        if (setMovies.empty())
            return;
        this->clear();
        m_mapFile2Item.clear();
        m_mapSn2Item.clear();
        m_mapDate2Item.clear();

        QString qstrMovieDir = (CFG()->MoviePath() + "\\").c_str();
        for (auto item : setMovies) {
            QString qstr = item.c_str();
            std::string strDate = "";
            QStringList qlist = qstr.split('-');
            if (qlist.length() != 2)
                continue;
            QString qstrPic = qstrMovieDir + qlist[0] + "\\" + qstr + "\\" + qstr + ".jpg";
            std::string strPic = qstrPic.toStdString();
            auto itMovie = MDB()->MovieInfo(item);
            if (itMovie.strDate != "") {
                strDate = itMovie.strDate;
                if (strDate.length() <= 11 && strDate.length() >= 10) {
                    if (strDate[0] == ' ')
                        strDate = strDate.substr(1, strDate.length()-1);
                    qstr += " \n" + QString(strDate.c_str());
                }
            }
            if (itMovie.strTitle != "") {
                qstr += " \n" + QString(itMovie.strTitle.c_str());
            }

            QPixmap pix("amms.png");
            if (PicCacheInst()->HasPixmap(strPic))
                PicCacheInst()->GetPixmap(strPic, pix);
            else {
                // pix.
                // PostEvent(CEventPtr(new CLoadPicReqEvent(strPic)));
                emit signalEventToParent(CEventObject(CEventPtr(new CLoadPicReqEvent(strPic))));
            }
            QIcon ic(pix);
            QListWidgetItem* pcItem = new QListWidgetItem(ic, qstr, this);
            m_mapFile2Item[strPic] = pcItem;
            m_mapSn2Item[item] = pcItem;
            m_mapDate2Item[strDate][item] = pcItem;
            this->addItem(pcItem);
        }
    }

    void CMovieWallWidget::SetIcon(const std::string &strIconFile)
    {
        if (m_mapFile2Item.count(strIconFile)) {
            QPixmap pix;
            PicCacheInst()->GetPixmap(strIconFile, pix);
            m_mapFile2Item[strIconFile]->setIcon(QIcon(pix));
            m_mapFile2Item[strIconFile]->setHidden(true);
            m_mapFile2Item[strIconFile]->setHidden(false);
        }
    }

    void CMovieWallWidget::slotItemDoubleClicked(QListWidgetItem* item)
    {
        QString qstr = item->text();
        auto listStr = qstr.split(" ");
        if (listStr.length() < 1)
            return;
        emit signalItemSelected(listStr[0]);
    }

    void CMovieWallWidget::slotEventFromParent(CEventObject objEvent)
    {
        auto pcEvent = objEvent.GetEvent();
        switch (pcEvent->Type()) {
        case etRspLoadPic: {
            CLoadPicRspEvent* pcRspEvent = (CLoadPicRspEvent*)(pcEvent.get());
            if (pcRspEvent && pcRspEvent->m_bSuccess) {
                SetIcon(pcRspEvent->m_strFileName);
            }
            break;
        }
        }
    }

}
