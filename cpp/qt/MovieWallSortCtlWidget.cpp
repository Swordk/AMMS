/////////////////////////////////////////////////////////////////////////﻿
///MovieWallSortCtlWidget
///20170813 jason wong 创建该文件
///控制MovieWallWidget排序
/////////////////////////////////////////////////////////////////////////

#include "MovieWallSortCtlWidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QString>

namespace amms {

    void CMovieWallSortCtlWidget::Init()
    {
        this->setStyleSheet("QLabel {border: 0px}; "
                            );
        QHBoxLayout* pcLayout = new QHBoxLayout(this);
        QLabel* pcLabel = new QLabel(this);
        pcLabel->setText(QStringLiteral("排序"));
        pcLayout->addWidget(pcLabel);

        m_pcBtnSortBySn = new QPushButton(this);
        m_pcBtnSortBySn->setStyleSheet("QPushButton:hover { color: blue} "
                                       "QPushButton:pressed { color: red } ");
        m_pcBtnSortBySn->setText(QStringLiteral("番号 ↓"));
        m_pcBtnSortBySn->setFixedWidth(100);
        pcLayout->addWidget(m_pcBtnSortBySn);

        m_pcBtnSortByDate = new QPushButton(this);
        m_pcBtnSortByDate->setStyleSheet("QPushButton:hover { color: blue} "
                                         "QPushButton:pressed { color: red } ");
        m_pcBtnSortByDate->setText(QStringLiteral("日期 ↓"));
        m_pcBtnSortByDate->setFixedWidth(100);
        pcLayout->addWidget(m_pcBtnSortByDate);

        this->setLayout(pcLayout);
        this->setFixedHeight(40);

        connect(m_pcBtnSortBySn, SIGNAL(clicked(bool)), this, SLOT(slotBtnSortBySnClicked()));
        connect(m_pcBtnSortByDate, SIGNAL(clicked(bool)), this, SLOT(slotBtnSortByDateClicked()));
    }

    void CMovieWallSortCtlWidget::slotBtnSortBySnClicked()
    {
        QString qstrText = m_pcBtnSortBySn->text();
        if (qstrText == QStringLiteral("番号 ↓")) {
            qstrText = QStringLiteral("番号 ↑");
            emit signalSortBySn(false);
        }
        else {
            qstrText = QStringLiteral("番号 ↓");
            emit signalSortBySn(true);
        }
        m_pcBtnSortBySn->setText(qstrText);
    }

    void CMovieWallSortCtlWidget::slotBtnSortByDateClicked()
    {
        QString qstrText = m_pcBtnSortByDate->text();
        if (qstrText == QStringLiteral("日期 ↓")) {
            qstrText = QStringLiteral("日期 ↑");
            emit signalSortByDate(false);
        }
        else {
            qstrText = QStringLiteral("日期 ↓");
            emit signalSortByDate(true);
        }
        m_pcBtnSortByDate->setText(qstrText);
    }
}
