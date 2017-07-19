/////////////////////////////////////////////////////////////////////////﻿
///MovieInfoWindow
///20160705 jason wong 创建该文件
///电影详情页面
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QString>
#include <QVector>

namespace amms {

    extern QVector<QString> GetMovieFiles(const QString& qstrPath);

    class CMovieInfoWindow : public QDialog {
        Q_OBJECT
    public:
        explicit CMovieInfoWindow(QWidget* pcParent = 0, Qt::WindowFlags flags = 0)
            : QDialog(pcParent, flags)
            , m_pcLabelTitle(NULL), m_pcGraphLabelCover(NULL)
            , m_pcLabel1(NULL), m_pcLabel2(NULL), m_pcLabel3(NULL), m_pcLabel4(NULL)
            , m_pcLabel5(NULL), m_pcLabel6(NULL), m_pcLabel7(NULL), m_pcLabel8(NULL)
            , m_pcListActors(NULL), m_pcListMovies(NULL)
            // , m_pcGraphLabelPreview(NULL)
            // , m_pcLabelPreviewCount(NULL)// , m_pcBtnPre(NULL)// , m_pcBtnNext(NULL)
            , m_qstrMovieDir("")
        {
        }
        virtual ~CMovieInfoWindow(){}

        void Init();

        void SetSn(const QString& qstrSn);

    private slots:
        void slotOpenDir();
        void slotMovieItemDoubleClicked(QListWidgetItem*);

    private:
        void Clear();

    private:
        QLabel* m_pcLabelTitle;
        QLabel* m_pcGraphLabelCover;
        QPushButton* m_pcBtnOpenDir;
        QLabel* m_pcLabel1;
        QLabel* m_pcLabel2;
        QLabel* m_pcLabel3;
        QLabel* m_pcLabel4;
        QLabel* m_pcLabel5;
        QLabel* m_pcLabel6;
        QLabel* m_pcLabel7;
        QLabel* m_pcLabel8;
        QListWidget* m_pcListActors;
        QListWidget* m_pcListMovies;
        // QLabel* m_pcGraphLabelPreview;
        // QLabel* m_pcLabelPreviewCount;
        // QPushButton* m_pcBtnPre;
        // QPushButton* m_pcBtnNext;

        QString m_qstrMovieDir;
    };

}
