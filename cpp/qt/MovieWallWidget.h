/////////////////////////////////////////////////////////////////////////﻿
///DynamicGridWidget
///20160919 jason wong 创建该文件
///随着窗口大小变化，可动态调整每行Widget数量的GridWidget
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <QString>
#include <QSize>
#include <QListWidget>
#include <QListWidgetItem>

namespace amms {

    class CMovieWallWidget : public QListWidget {
        Q_OBJECT
    public:
        //构造函数
        explicit CMovieWallWidget(QWidget * parent = 0)
            : QListWidget(parent)

        {}
        //析构函数
        virtual ~CMovieWallWidget() {}

        //
        void Init(QSize frameSize);

        void AddItem(const QString& qstrTxt, const QString& qstrPic);

    signals:
        void signalItemSelected(QString qstrSn);

    public slots:
        void slotItemDoubleClicked(QListWidgetItem *item);
    };
}

