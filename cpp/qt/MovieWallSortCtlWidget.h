/////////////////////////////////////////////////////////////////////////﻿
///MovieWallSortCtlWidget
///20170813 jason wong 创建该文件
///控制MovieWallWidget排序
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <QObject>
#include <QWidget>
#include <QPushButton>

namespace amms {

    class CMovieWallSortCtlWidget : public QWidget {
        Q_OBJECT
    public:
        explicit CMovieWallSortCtlWidget(QWidget* pcParent)
            : QWidget(pcParent)
        {}
        virtual ~CMovieWallSortCtlWidget(){}

        void Init();

    signals:
        void signalSortBySn(bool bEsc);
        void signalSortByDate(bool bEsc);

    private slots:
        void slotBtnSortBySnClicked();
        void slotBtnSortByDateClicked();

    private:
        QPushButton* m_pcBtnSortBySn;
        QPushButton* m_pcBtnSortByDate;
    };
}
