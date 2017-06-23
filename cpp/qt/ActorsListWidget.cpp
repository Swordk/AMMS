/////////////////////////////////////////////////////////////////////////﻿
///ActorsListWidget.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "ActorsListWidget.h"
#include <QStringList>
#include <QMap>
#include <QHeaderView>

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
            this->AddRow();
            auto pcItem = this->item(nRowIndex, 0);
            if (pcItem)
                pcItem->setText(item.first.c_str());
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
