/////////////////////////////////////////////////////////////////////////﻿
///PicLoader.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "PicLoader.h"
#include "PicCache.h"

namespace amms {
    void CPicLoader::Init()
    {
        this->RegisterEventProcesser(EU_EventType::etReqLoadPic);
    }

    void CPicLoader::_ProcessEvent(CEventPtr &pcEvent)
    {
        switch (pcEvent->Type()) {
        case EU_EventType::etReqLoadPic: {
            CLoadPicReqEvent* pcReqEvent = (CLoadPicReqEvent*)(pcEvent.get());
            if (pcReqEvent) {
                std::string strFile = pcReqEvent->m_strFileName;

                bool bRtn = PicCacheInst()->LoadPixmap(strFile);
                CLoadPicRspEvent* pcRspEvent = new CLoadPicRspEvent(strFile);
                if (bRtn)
                    pcRspEvent->m_bSuccess = true;
                else
                    pcRspEvent->m_bSuccess = false;
                PostEvent(CEventPtr(pcRspEvent));
            }
            break;
        }
        }
    }
}
