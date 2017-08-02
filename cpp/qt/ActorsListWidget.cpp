/////////////////////////////////////////////////////////////////////////﻿
///ActorsListWidget.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "ActorsListWidget.h"
#include <QStringList>
#include <QMap>
#include <QHeaderView>

#include "MDataBase.h"

namespace amms {
    void CActorsListWidget::Init()
    {
        this->setStyleSheet(QString("font-size: 14px; border: 0px;"));
        this->setEditTriggers(QTableWidget::NoEditTriggers);        //设置不可编辑

        this->AddColumn("ActorName", QStringLiteral("演员").toStdString(), 120);
        this->AddColumn("Grand", QStringLiteral("评分").toStdString(), 50);
        this->AddColumn("Count", QStringLiteral("数量").toStdString(), 50);
        this->AddColumn("BirthDay", QStringLiteral("生日").toStdString(), 90);
        this->AddColumn("Cup", "Cup", 40);
        this->AddColumn("Height", QStringLiteral("身高").toStdString(), 60);
        this->verticalHeader()->setHidden(true);                    // 隐藏行号
        this->InitColumns(true);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);

        connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(slotCellSelected(int, int)));
    }

    void CActorsListWidget::SetActors(const std::map<std::string, std::set<std::string> >& mapActors2Sn)
    {
        int nActorsCount = mapActors2Sn.size();
        if (nActorsCount <= 0)
            return;
        this->clearContents();

        int nRowIndex = 0;
        for (auto& item : mapActors2Sn) {
            std::string strActorName = item.first;
            auto actorInfo = MDB()->ActorInfo(strActorName);
            auto actorMovieCount = MDB()->ActorMovieCount(strActorName);

            this->AddRow();
            auto pcItem = this->item(nRowIndex, 0);
            if (pcItem)
                pcItem->setText(strActorName.c_str());
            pcItem = this->item(nRowIndex, 2);
            if (pcItem)
                pcItem->setData(Qt::DisplayRole, actorMovieCount);
            pcItem = this->item(nRowIndex, 3);
            if (pcItem)
                pcItem->setText(actorInfo.strBirthDay.c_str());
            pcItem = this->item(nRowIndex, 4);
            if (pcItem)
                pcItem->setText(actorInfo.strCup.c_str());
            pcItem = this->item(nRowIndex, 5);
            if (pcItem)
                pcItem->setText(actorInfo.strHeight.c_str());
            ++nRowIndex;
        }
    }

    void CActorsListWidget::slotCellSelected(int row, int col)
    {
        auto pcItem = this->item(row, 0);
        if (pcItem == NULL)
            return;
        emit signalActorSelected(pcItem->text());
    }
}
