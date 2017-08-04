/////////////////////////////////////////////////////////////////////////﻿
///DynamicGridWidget
///20160919 jason wong 创建该文件
///随着窗口大小变化，可动态调整每行Widget数量的GridWidget
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <set>
#include <map>
#include <QString>
#include <QSize>
#include <QListWidget>
#include <QListWidgetItem>
#include "EventObject.h"

namespace amms {

    class CMovieWallWidget : public QListWidget {
        Q_OBJECT
    public:
        //构造函数
        explicit CMovieWallWidget(QWidget * parent = 0)
            : QListWidget(parent)
            , m_mapFile2Item()
        {}
        //析构函数
        virtual ~CMovieWallWidget() {}

        //
        void Init(QSize frameSize);

        void SetMovies(const std::set<std::string>& setMovies);
        void SetIcon(const std::string& strIconFile);

    signals:
        void signalItemSelected(QString qstrSn);
        void signalEventToParent(CEventObject);


    public slots:
        void slotItemDoubleClicked(QListWidgetItem *item);

        void slotEventFromParent(CEventObject);

    private:
        std::map<std::string, QListWidgetItem*> m_mapFile2Item;
        std::map<std::string, QListWidgetItem*> m_mapSn2Item;
        std::map<std::string, std::map<std::string, QListWidgetItem*> > m_mapDate2Item;
    };
}

