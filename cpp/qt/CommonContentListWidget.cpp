/////////////////////////////////////////////////////////////////////////﻿
///CommonContentListWidget
///20170802 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "CommonContentListWidget.h"
#include <QStringList>
#include <QMap>
#include <QHeaderView>

#include "MDataBase.h"

namespace amms {
    void CCommonContentListWidget::Init(const std::string& strColName)
    {
        this->setStyleSheet(QString("font-size: 14px; border: 0px;"));
        this->setEditTriggers(QTableWidget::NoEditTriggers);        //设置不可编辑

        this->AddColumn("ContentCol", strColName, 180);
        this->AddColumn("Count", QStringLiteral("数量").toStdString(), 50);
        this->verticalHeader()->setHidden(true);                    // 隐藏行号
        this->InitColumns(true);
        this->setSelectionBehavior(QAbstractItemView::SelectRows);

        connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(slotCellSelected(int, int)));
    }

    void CCommonContentListWidget::SetContents(const std::map<std::string, int>& mapContent2Count)
    {
        int nContentsSize = mapContent2Count.size();
        if (nContentsSize <= 0)
            return;
        this->clearContents();
        this->setRowCount(0);

        int nRowIndex = 0;
        for (auto& item : mapContent2Count) {
            std::string strContents = item.first;
            auto nContentsCount = item.second;

            this->AddRow();
            auto pcItem = this->item(nRowIndex, 0);
            if (pcItem)
                pcItem->setText(strContents.c_str());
            pcItem = this->item(nRowIndex, 1);
            if (pcItem)
                pcItem->setData(Qt::DisplayRole, nContentsCount);
            ++nRowIndex;
        }
    }

    void CCommonContentListWidget::slotCellSelected(int row, int col)
    {
        auto pcItem = this->item(row, 0);
        if (pcItem == NULL)
            return;
        emit signalContentSelected(pcItem->text());
    }
}
