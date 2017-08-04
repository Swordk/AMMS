/////////////////////////////////////////////////////////////////////////﻿
///自定义TableWidget
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <math.h>
#include <string>
#include <QLabel>
#include <QTableWidget>

namespace amms {
    struct ColumnDesc_ST {
        int iIndex;
        std::string strId;
        std::string strDesc;
        int iWidth;
        bool bSort;
        bool bHidden;

    public:
        ColumnDesc_ST() {}
        ColumnDesc_ST(int v_iIndex, std::string v_strId, std::string v_strDesc, int v_iWidth, bool v_bSort, bool v_bHidden) {
            iIndex = v_iIndex;
            strId = v_strId;
            strDesc = v_strDesc;
            iWidth = v_iWidth;
            bSort = v_bSort;
            bHidden = v_bHidden;
        }
    };

    class CTableWidget : public QTableWidget {
        Q_OBJECT
    public:
        //构造函数
        CTableWidget(QWidget *v_pcParent) : QTableWidget(v_pcParent), m_iColumnIndex(0) {}

        //析构函数
        virtual ~CTableWidget() {}

        // return added row id
        int AddRow();
        int InsertRow(int nRow);

        //
        void AddColumn(std::string v_strId, std::string v_strDesc, int v_iWidth, bool v_bSort, bool v_bHidden) {
            m_vecColumnDescs.push_back(ColumnDesc_ST(m_iColumnIndex, v_strId, v_strDesc, v_iWidth, v_bSort, v_bHidden));
            m_mapColumnDescs[v_strId] = ColumnDesc_ST(m_iColumnIndex, v_strId, v_strDesc, v_iWidth, v_bSort, v_bHidden);
            m_iColumnIndex++;
        }

        //
        void AddColumn(std::string v_strId, std::string v_strDesc, int v_iWidth) {
            this->AddColumn(v_strId, v_strDesc, v_iWidth, false, false);
        }

        //
        void AddHiddenColumn(std::string v_strId, std::string v_strDesc, int v_iWidth) {
            this->AddColumn(v_strId, v_strDesc, v_iWidth, false, true);
        }

        //
        inline int GetColumnIndex(std::string v_strId) {
            return m_mapColumnDescs[v_strId].iIndex;
        }

        //
        int GetTotalWidth() {
            int iWidth = 0;
            for(auto& item: m_mapColumnDescs) {
                iWidth += item.second.iWidth;
            }
            return iWidth;
        }

        //
        void InitColumns(bool bSortable = true);

        //
        void SetText(int v_iRowId, std::string v_strColumn, std::string v_strContent);

        //
        void SetText(int v_iRowId, std::string v_strColumn, std::string v_strContent, const QColor& v_pcColor);

        //
        const QColor GetColor(double v_fValue) {
            if(fabs(v_fValue) < 0.000001) {
                return Qt::black;
            }
            else if(v_fValue > 0) {
                return Qt::red;
            }
            else {
                return Qt::darkGreen;
            }
        }

    protected:
        bool InitRow(int nRow);

    public slots:
        //
        void slotSort(int v_iColumnIndex);

    protected:
        std::vector<ColumnDesc_ST> m_vecColumnDescs;
        std::map<std::string, ColumnDesc_ST> m_mapColumnDescs;     //key为strId
        int m_iColumnIndex;
    };
}

