/////////////////////////////////////////////////////////////////////////﻿
///ScanDiskProcesser
///20160818 jason wong 创建该文件
///遍历硬盘目录
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <QString>
#include "EventProcesser.h"

namespace amms {

    class CScanDiskProcesser : public CEventProcesser {
    public:
        explicit CScanDiskProcesser(CEventRouter* pcRouter)
            : CEventProcesser(false, pcRouter)
            , m_bStop(true)
        {}

        void Init();
        inline void StopScan() {
            m_bStop = true;
        }

    protected:
        virtual void _ProcessEvent(CEventPtr& pcEvent) override;

        void ScanDisk(const QString& qstrMoviePath, bool bIsSn = true);

    private:
        bool m_bStop;

    };
}
