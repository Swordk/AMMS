/////////////////////////////////////////////////////////////////////////﻿
///EventRouter.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "EventRouter.h"

#include "Typedef.h"

namespace amms {

    //注册EventHandler
    void CEventRouter::RegisterEventHandler(const EU_EventType& v_euEventType, CEventProcesser* v_pcEventProcesser, int v_iPriority)
    {
        writeLock wlLock(m_mtxProcessers);
        if (m_mapProcessers.count(v_euEventType) < 0) {
            m_mapProcessers[v_euEventType] = std::vector<EventProcesserNode_ST>();
        }

        EventProcesserNode_ST stNode;
        stNode.m_pcProcesser = v_pcEventProcesser;
        stNode.m_iPriority = v_iPriority;
        m_mapProcessers[v_euEventType].push_back(stNode);
        std::stable_sort(m_mapProcessers[v_euEventType].begin(), m_mapProcessers[v_euEventType].end());
    }

    void CEventRouter::CancelRegisterEventHandler(const EU_EventType& v_euEventType, CEventProcesser* v_pcEventProcesser)
    {
        if (v_pcEventProcesser == NULL)
            return;
        writeLock wlLock(m_mtxProcessers);
        if (m_mapProcessers.count(v_euEventType) <= 0)
            return;

        for (auto item = m_mapProcessers[v_euEventType].begin(); item != m_mapProcessers[v_euEventType].end(); ++item) {
            if (item->m_pcProcesser == v_pcEventProcesser) {
                m_mapProcessers[v_euEventType].erase(item);
                break;
            }
        }
    }

    //发送Event
    void CEventRouter::DispatchEvent(CEventPtr& v_pcEvent)
    {
        readLock rdLock(m_mtxProcessers);
        for (EventProcesserNode_ST &stNode : m_mapProcessers[v_pcEvent->Type()]) {
            stNode.m_pcProcesser->ProcessEvent(v_pcEvent);
        }
    }
}
