/////////////////////////////////////////////////////////////////////////﻿
///MovieInfoWindow
///20160705 jason wong 创建该文件
///电影详情页面
/////////////////////////////////////////////////////////////////////////

#include "MovieInfoWindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProcess>
#include <QDir>
#include "Config.h"
#include "MDataBase.h"

namespace amms {
    void CMovieInfoWindow::Init()
    {
        this->setStyleSheet("QLabel {font-size: 20px; color: rgb(128, 128, 255); }; QWidget {border: 0px}; ");
        QVBoxLayout* pcLayout = new QVBoxLayout(this);
        m_pcLabelTitle = new QLabel(this);
        m_pcLabelTitle->setStyleSheet("font-weight: bold; color: rgb(255,120,255); font-size: 30px");
        QWidget* pcMovieCoverWidget = new QWidget(this);
        QHBoxLayout* pcMovieCoverLayout = new QHBoxLayout(pcMovieCoverWidget);
        m_pcGraphLabelCover = new QLabel(pcMovieCoverWidget);
        m_pcGraphLabelCover->setMinimumWidth(800);
        m_pcGraphLabelCover->setMaximumWidth(1000);

        QWidget* pcMovieInfoWidget = new QWidget(this);
        QVBoxLayout* pcMovieInfoLayout = new QVBoxLayout(pcMovieInfoWidget);
        m_pcBtnOpenDir = new QPushButton(this);
        m_pcLabel1 = new QLabel(pcMovieInfoWidget);
        m_pcLabel2 = new QLabel(pcMovieInfoWidget);
        m_pcLabel3 = new QLabel(pcMovieInfoWidget);
        m_pcLabel4 = new QLabel(pcMovieInfoWidget);
        m_pcLabel5 = new QLabel(pcMovieInfoWidget);
        m_pcLabel6 = new QLabel(pcMovieInfoWidget);
        m_pcLabel7 = new QLabel(pcMovieInfoWidget);
        m_pcLabel8 = new QLabel(pcMovieInfoWidget);
        m_pcLabel1->hide();
        m_pcLabel2->hide();
        m_pcLabel3->hide();
        m_pcLabel4->hide();
        m_pcLabel5->hide();
        m_pcLabel6->hide();
        m_pcLabel7->hide();
        m_pcLabel8->hide();
        m_pcBtnOpenDir->setText(QStringLiteral("打开目录"));
        m_pcBtnOpenDir->setStyleSheet("QPushButton { font-size: 26px; font-weight:normal; color: pink; border: 0px } "
                                      "QPushButton:hover { font-weight:bold; } "
                                      "QPushButton:pressed { font-weight:bold; color: red } ");
        m_pcLabel7->setWordWrap(true);
        connect(m_pcBtnOpenDir, SIGNAL(clicked()), this, SLOT(slotOpenDir()));

        pcMovieInfoLayout->addWidget(m_pcBtnOpenDir);
        pcMovieInfoLayout->addWidget(m_pcLabel1);
        pcMovieInfoLayout->addWidget(m_pcLabel2);
        pcMovieInfoLayout->addWidget(m_pcLabel3);
        pcMovieInfoLayout->addWidget(m_pcLabel4);
        pcMovieInfoLayout->addWidget(m_pcLabel5);
        pcMovieInfoLayout->addWidget(m_pcLabel6);
        pcMovieInfoLayout->addWidget(m_pcLabel7);
        pcMovieInfoLayout->addWidget(m_pcLabel8);
        pcMovieInfoWidget->setLayout(pcMovieInfoLayout);

        pcMovieCoverLayout->addWidget(m_pcGraphLabelCover);
        pcMovieCoverLayout->addWidget(pcMovieInfoWidget);
        pcMovieCoverWidget->setLayout(pcMovieCoverLayout);


        m_pcListActor = new QListWidget(this);
        m_pcListActor->setIconSize(QSize(130, 130));
        m_pcListActor->setViewMode(QListView::IconMode);
        m_pcListActor->setMaximumHeight(155);

        // m_pcGraphLabelPreview = new QLabel(this);
        // m_pcLabelPreviewCount = new QLabel(this);
        // m_pcBtnPre = new QPushButton(this);
        // m_pcBtnNext = new QPushButton(this);

        pcLayout->addWidget(m_pcLabelTitle);
        pcLayout->addWidget(pcMovieCoverWidget);
        pcLayout->addWidget(m_pcListActor);
        this->setLayout(pcLayout);
    }

    void CMovieInfoWindow::SetSn(const QString& qstrSn)
    {
        Clear();
        if (qstrSn == "")
            return;
        QStringList snSplit = qstrSn.split("-");
        if (snSplit.length() != 2)
            return;
        SMovieInfo movieInfo = MDB()->MovieInfo(qstrSn.toStdString());
        QString qstrTitle = qstrSn + " " + movieInfo.strTitle.c_str();
        this->setWindowTitle(qstrTitle + QStringLiteral("   - amms, 您的私人电影数据库"));
        m_pcLabelTitle->setText(qstrTitle);
        m_pcLabelTitle->show();

        m_qstrMovieDir = CFG()->MoviePath().c_str() + QString("\\") + snSplit[0] + "\\" + qstrSn;
        QString qstrActorPath = CFG()->DbPath().c_str() + QString("\\actor_pic");
        QPixmap pix(m_qstrMovieDir + "\\" + qstrSn + ".jpg");
        m_pcGraphLabelCover->setPixmap(pix);
        m_pcGraphLabelCover->show();

        if (movieInfo.strDate != "") {
            m_pcLabel1->setText(QStringLiteral("发布日期: ") + movieInfo.strDate.c_str());
            m_pcLabel1->show();
        }
        if (movieInfo.nMinutes != 0) {
            m_pcLabel2->setText(QStringLiteral("时长: ")
                + QString::number(movieInfo.nMinutes) + QStringLiteral("分钟"));
            m_pcLabel2->show();
        }
        if (movieInfo.strDirector != "") {
            m_pcLabel3->setText(QStringLiteral("导演: ") + movieInfo.strDirector.c_str());
            m_pcLabel3->show();;
        }
        if (movieInfo.strProducer != "") {
            m_pcLabel4->setText(QStringLiteral("制作商: ") + movieInfo.strProducer.c_str());
            m_pcLabel4->show();
        }
        if (movieInfo.strPublisher != "") {
            m_pcLabel5->setText(QStringLiteral("发行商: ") + movieInfo.strPublisher.c_str());
            m_pcLabel5->show();
        }
        if (movieInfo.strSeries != "") {
            m_pcLabel6->setText(QStringLiteral("系列: ") + movieInfo.strSeries.c_str());
            m_pcLabel6->show();
        }
        if (movieInfo.setGenres.empty() == false) {
            QString qstrGenres = QStringLiteral("类别: ");
            for (auto& item : movieInfo.setGenres) {
                qstrGenres += QString(" ") + item.c_str();
            }
            m_pcLabel7->setText(qstrGenres);
            m_pcLabel7->show();
        }

        if (movieInfo.setActors.empty() == false) {
            m_pcListActor->clear();
            for (auto& itActor : movieInfo.setActors) {
                QPixmap pix(qstrActorPath + "\\" + QString(itActor.c_str()) + ".jpg");
                QIcon ic(pix);
                QListWidgetItem* item = new QListWidgetItem(ic, itActor.c_str(), m_pcListActor);
                m_pcListActor->addItem(item);
            }
            m_pcListActor->show();
        }
    }

    void CMovieInfoWindow::slotOpenDir()
    {
        if (m_qstrMovieDir != "") {
            QProcess p(0);
            p.start("explorer.exe", QStringList(m_qstrMovieDir));
            p.waitForFinished();    //等待完成
        }
    }

    void CMovieInfoWindow::Clear()
    {
        m_pcLabelTitle->hide();
        m_pcGraphLabelCover->hide();
        m_pcLabel1->hide();
        m_pcLabel2->hide();
        m_pcLabel3->hide();
        m_pcLabel4->hide();
        m_pcLabel5->hide();
        m_pcLabel6->hide();
        m_pcLabel7->hide();
        m_pcLabel8->hide();
        m_pcListActor->hide();
        // m_pcGraphLabelPreview->hide();
        // m_pcLabelPreviewCount->hide();
        // m_pcBtnPre->hide();
        // m_pcBtnNext->hide();
        m_qstrMovieDir = "";
    }


}
