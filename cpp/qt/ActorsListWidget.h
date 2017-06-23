/////////////////////////////////////////////////////////////////////////﻿
///ActorsListWidget.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <map>
#include <string>
#include <set>
#include <QObject>
#include <QWidget>
#include <QString>
#include "TableWidget.h"

namespace amms {
    class CActorsListWidget : public CTableWidget {
            Q_OBJECT
    public:
        explicit CActorsListWidget(QWidget *parent)
            : CTableWidget(parent)
        {}
        virtual ~CActorsListWidget(){}

    public:
        void Init();
        void SetActors(const std::map<std::string, std::set<std::string> >& mapActors2Sn);

    signals:
        void signalActorSelected(QString actor);

    public slots:
        void slotCellSelected(int, int);


    };

}
