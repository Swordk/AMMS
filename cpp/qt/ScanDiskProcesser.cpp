/////////////////////////////////////////////////////////////////////////﻿
///ScanDiskProcesser
///20160818 jason wong 创建该文件
///遍历硬盘目录
/////////////////////////////////////////////////////////////////////////

#include "ScanDiskProcesser.h"
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include "Config.h"
#include "MDataBase.h"

namespace amms {

    void CScanDiskProcesser::Init()
    {
        this->RegisterEventProcesser(etCmdStartScanDisk);
        this->RegisterEventProcesser(etCmdStopScanDisk);
    }

    void CScanDiskProcesser::_ProcessEvent(CEventPtr& pcEvent)
    {
        switch (pcEvent->Type()) {
        case etCmdStartScanDisk: {
            m_bStop = false;
            ScanDisk(CFG()->MoviePath().c_str(), false);
            PostEvent(CEventPtr(new CEvent(etRspMovieScanFinished)));
        }
        }
    }

    void CScanDiskProcesser::ScanDisk(const QString& qstrMoviePath, bool bIsSn)
    {
        QDir dirSeries(qstrMoviePath);
        if (!dirSeries.exists())
            return;
        // 只遍历目录，如果包含文件，使用"QDir::Dirs|QDir::Files"
        dirSeries.setFilter(QDir::Dirs);
        QFileInfoList filelistSeries = dirSeries.entryInfoList();

        for (auto& item : filelistSeries) {
            if (m_bStop)
                return;
            auto itName = item.fileName();
            if (itName == "." || itName == "..")
                continue;
            if (!bIsSn) {
                auto itPath = item.filePath();
                ScanDisk(itPath);
            }
            else {
                auto strMovieName = itName.toStdString();
                MDB()->AddDiskMovie(strMovieName);
            }
        }
    }
}
