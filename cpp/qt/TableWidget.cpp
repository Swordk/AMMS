/////////////////////////////////////////////////////////////////////////
///自定义TableWidget
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include <QHeaderView>
#include "TableWidget.h"

using namespace amms;

int CTableWidget::AddRow()
{
    int nRowCount = rowCount();
    setRowCount(nRowCount+1);
    InitRow(nRowCount);
    return nRowCount;
}

int CTableWidget::InsertRow(int nRow)
{
    int nRowCount = rowCount();
    if (nRow >= nRowCount)
        return -1;
    insertRow(nRow);
    InitRow(nRow);
    return nRow;
}

//
void CTableWidget::InitColumns(bool bSortable)
{
    this->setColumnCount(m_vecColumnDescs.size());

    QStringList header;
    for(auto& item: m_vecColumnDescs) {
        this->setColumnWidth(item.iIndex, item.iWidth);
        this->setColumnHidden(item.iIndex, item.bHidden);
        header.append(QObject::tr(item.strDesc.c_str()));
    }
    this->setHorizontalHeaderLabels(header);

    if (bSortable)
        connect(this->horizontalHeader(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(slotSort(int)));
}

bool CTableWidget::InitRow(int nRow)
{
    for (int nCol = 0; nCol < columnCount(); ++nCol) {
        QTableWidgetItem* pcItem = new QTableWidgetItem();
        pcItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        setItem(nRow, nCol, pcItem);
    }
    return nRow;
}

//
void CTableWidget::slotSort(int v_iColumnIndex)
{
    this->sortByColumn(v_iColumnIndex);
}

//
void CTableWidget::SetText(int v_iRowId, string v_strColumn, string v_strContent)
{
    this->item(v_iRowId, this->GetColumnIndex(v_strColumn))->setText(v_strContent.c_str());
}

//
void CTableWidget::SetText(int v_iRowId, string v_strColumn, string v_strContent, const QColor& v_pcColor)
{
    this->item(v_iRowId, this->GetColumnIndex(v_strColumn))->setText(v_strContent.c_str());
    this->item(v_iRowId, this->GetColumnIndex(v_strColumn))->setTextColor(v_pcColor);
}
