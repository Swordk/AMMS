/////////////////////////////////////////////////////////////////////////﻿
///ActorInfoWidget
///20160704 jason wong 创建该文件
///演员详情页面
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QListWidget>
namespace amms {
    class CActorInfoWidget : public QWidget {
        Q_OBJECT
    public:
        //构造函数
        explicit CActorInfoWidget(QWidget * parent = 0)
            : QWidget(parent)
            , m_pcGraphLabel(NULL)
        {}
        //析构函数
        virtual ~CActorInfoWidget() {}

        void Init();

    public slots:
        void slotSetlActor(QString actor);


    private:
        QLabel*             m_pcGraphLabel;
        QLabel*             m_pcActorInfoLabel1;
        QLabel*             m_pcActorInfoLabel2;
        QLabel*             m_pcActorInfoLabel3;
        QLabel*             m_pcActorInfoLabel4;


    };
}
