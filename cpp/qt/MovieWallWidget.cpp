/////////////////////////////////////////////////////////////////////////﻿
///DynamicGridWidget
///20160919 jason wong 创建该文件
///随着窗口大小变化，可动态调整每行Widget数量的GridWidget
/////////////////////////////////////////////////////////////////////////

#include "MovieWallWidget.h"
#include <QStringList>

namespace amms {
    void CMovieWallWidget::Init(QSize frameSize)
    {
        this->setViewMode(QListView::IconMode);
        this->setIconSize(frameSize);
        this->setResizeMode(QListView::ResizeMode::Adjust);
        this->setMovement(QListView::Movement::Static);
        this->setSpacing(5);
        connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slotItemDoubleClicked(QListWidgetItem*)));
    }

    void CMovieWallWidget::AddItem(const QString& qstrTxt, const QString& qstrPic)
    {
        QPixmap pix(qstrPic);
        // QIcon ic = QIcon(pix.scaled(212, 300));
        QIcon ic(pix);
        QListWidgetItem* item = new QListWidgetItem(ic, qstrTxt, this);
        //item->
    }
    void CMovieWallWidget::slotItemDoubleClicked(QListWidgetItem* item)
    {
        QString qstr = item->text();
        auto listStr = qstr.split(" ");
        if (listStr.length() < 1)
            return;
        emit signalItemSelected(listStr[0]);
    }
}
