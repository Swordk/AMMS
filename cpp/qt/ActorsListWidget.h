/////////////////////////////////////////////////////////////////////////﻿
///ActorsListWidget.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <QObject>
#include <QWidget>
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

    };

}
