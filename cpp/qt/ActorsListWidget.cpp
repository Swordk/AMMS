/////////////////////////////////////////////////////////////////////////﻿
///ActorsListWidget.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "ActorsListWidget.h"
#include <QStringList>
#include <QMap>

namespace amms {
    void CActorsListWidget::Init()
    {
        this->setStyleSheet(QString("font-size: 14px; border: 0px;"));
        this->setEditTriggers(QTableWidget::NoEditTriggers);        //设置不可编辑

        this->AddColumn("ActorName", "ActorName", 120);
        this->AddColumn("Grand", "Grand", 50);
        this->AddColumn("BirthDay", "BirthDay", 70);
        this->AddColumn("Cup", "Cup", 40);
        this->AddColumn("Height", "Height", 60);
        this->AddColumn("Weight", "Weight", 60);

        this->InitColumns(true);



    }
}
