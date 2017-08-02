/////////////////////////////////////////////////////////////////////////﻿
///CommonContentListWidget
///20170802 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <map>
#include <string>
#include <set>
#include <QObject>
#include <QWidget>
#include <QString>
#include "TableWidget.h"

namespace amms {
    class CCommonContentListWidget : public CTableWidget {
            Q_OBJECT
    public:
        explicit CCommonContentListWidget(QWidget *parent)
            : CTableWidget(parent)
        {}
        virtual ~CCommonContentListWidget(){}

    public:
        void Init(const std::string& strColName);
        void SetContents(const std::map<std::string, int>& mapContent2Count);

    signals:
        void signalContentSelected(QString qstrContent);

    public slots:
        void slotCellSelected(int, int);


    };

}
