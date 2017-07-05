/////////////////////////////////////////////////////////////////////////﻿
///ActorInfoWidget
///20160704 jason wong 创建该文件
///演员详情页面
/////////////////////////////////////////////////////////////////////////

#include "ActorInfoWidget.h"
#include <QHBoxLayout>
#include <QListWidgetItem>
#include "MDataBase.h"
#include "Config.h"

namespace amms {
    void CActorInfoWidget::Init()
    {
        this->setStyleSheet("QLabel {font-size: 20px}");
        QHBoxLayout* pcLayout = new QHBoxLayout(this);
        m_pcGraphLabel = new QLabel(this);
        m_pcGraphLabel->setStyleSheet("border: none");
        m_pcGraphLabel->setFixedSize(130, 130);

        m_pcActorInfoLabel1 = new QLabel(this);
        m_pcActorInfoLabel1->setStyleSheet("font-weight: bold; color: pink; font-size: 24px");
        m_pcActorInfoLabel2 = new QLabel(this);
        m_pcActorInfoLabel2->setStyleSheet("color: rgb(0, 128, 255);");
        m_pcActorInfoLabel3 = new QLabel(this);
        m_pcActorInfoLabel3->setStyleSheet("color: rgb(255,160,255);");
        m_pcActorInfoLabel4 = new QLabel(this);
        m_pcActorInfoLabel4->setStyleSheet("color: rgb(128, 128, 255);");
        m_pcActorInfoLabel4->setWordWrap(true);

        pcLayout->addWidget(m_pcGraphLabel);
        pcLayout->addWidget(m_pcActorInfoLabel1);
        pcLayout->addWidget(m_pcActorInfoLabel2);
        pcLayout->addWidget(m_pcActorInfoLabel3);
        pcLayout->addWidget(m_pcActorInfoLabel4);

        this->setLayout(pcLayout);
        this->setFixedHeight(130);
        this->setMaximumWidth(900);
    }

    void CActorInfoWidget::slotSetlActor(QString actor)
    {
        QString qstrDbPath = CFG()->strDbPath().c_str();
        QString qstrPicFile = qstrDbPath + "/actor_pic/" + actor + ".jpg";
        QPixmap pix(qstrPicFile);
        m_pcGraphLabel->setPixmap(pix);

        SActorInfo actorInfo = MDB()->ActorInfo(actor.toStdString());
        QString qstrInfo = "";
        if (actorInfo.strName != "") {
            qstrInfo = actorInfo.strName.c_str();
            m_pcActorInfoLabel1->setText(qstrInfo);
        }
        else
            m_pcActorInfoLabel1->hide();

        qstrInfo = "";
        if (actorInfo.strHeight != "") {
            qstrInfo = QStringLiteral("身高: ") + actorInfo.strHeight.c_str();
        }
        if (actorInfo.strBirthDay != "") {
            if (qstrInfo.length() > 0)
                qstrInfo += "\n";
            qstrInfo += QStringLiteral("生日: ") + actorInfo.strBirthDay.c_str();
        }
        if (actorInfo.strCup != "") {
            if (qstrInfo.length() > 0)
                qstrInfo += "\n";
            qstrInfo += QStringLiteral("罩杯: ") + actorInfo.strCup.c_str();
        }
        if (qstrInfo.length() > 0) {
            m_pcActorInfoLabel2->setText(qstrInfo);
            m_pcActorInfoLabel2->show();
        }
        else
            m_pcActorInfoLabel2->hide();

        qstrInfo = "";
        if (actorInfo.strBust != "") {
            qstrInfo = QStringLiteral("胸围: ") + actorInfo.strBust.c_str();
        }
        if (actorInfo.strWaist != "") {
            if (qstrInfo.length() > 0)
                qstrInfo += "\n";
            qstrInfo += QStringLiteral("腰围: ") + actorInfo.strWaist.c_str();
        }
        if (actorInfo.strHip != "") {
            if (qstrInfo.length() > 0)
                qstrInfo += "\n";
             qstrInfo += QStringLiteral("臀围: ") + actorInfo.strHip.c_str();
        }
        if (qstrInfo.length() > 0) {
            m_pcActorInfoLabel3->setText(qstrInfo);
            m_pcActorInfoLabel3->show();
        }
        else
            m_pcActorInfoLabel3->hide();

        qstrInfo = "";
        if (actorInfo.setHobby.empty() == false) {
            qstrInfo = QStringLiteral("爱好: ");
            for (auto& item : actorInfo.setHobby) {
                qstrInfo += item.c_str() + QString("  ");
            }
            m_pcActorInfoLabel4->setText(qstrInfo);
            m_pcActorInfoLabel4->show();
        }
        else
            m_pcActorInfoLabel4->hide();

    }
}
