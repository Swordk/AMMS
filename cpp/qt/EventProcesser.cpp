/////////////////////////////////////////////////////////////////////////﻿
///EventProcesser.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "EventProcesser.h"

namespace amms {

    //Event异步处理函数
    void AsyncProcessEvent(CEventProcesser *pcEventProcesser)
    {
        pcEventProcesser->AsyncLoop();
    }

    //构造函数
    CEventProcesser::CEventProcesser(bool bIsSynchronized, CEventRouter* pcEventRouter)
    {
        m_bRunningFlag = true;
        m_bIsStoped = false;

        m_bIsSynchronized = bIsSynchronized;
        if (!bIsSynchronized) {
            ///异步方式的话启动线程
            boost::thread threadProcessEvent(boost::bind(&AsyncProcessEvent, this));
            threadProcessEvent.detach();
        }

        m_pcEventRouter = pcEventRouter;
    }

    //循环处理，异步处理时使用
    void CEventProcesser::AsyncLoop()
    {
        boost::mutex::scoped_lock lk(m_mtxCondEvents);

        while (m_bRunningFlag) {
            m_condEvents.wait(lk);

            while (true) {
                m_mtxEvents.lock();
                if (m_queueEvents.size() <= 0) {
                    m_mtxEvents.unlock();
                    break;
                }
                CEventPtr pcEvent = m_queueEvents.front();
                m_queueEvents.pop();
                m_mtxEvents.unlock();
                if (pcEvent && pcEvent->Type() == etStopEventProcesser) {
                    m_bRunningFlag = false;
                    break;
                }
                //处理
                this->_ProcessEvent(pcEvent);
            }
        }
        m_bIsStoped = true;
    }


    //注册EventProcesser
    void CEventProcesser::RegisterEventProcesser(const EU_EventType& euEventType)
    {
        m_pcEventRouter->RegisterEventHandler(euEventType, this, eppNormal);
        m_setRegisteredEvent.insert(euEventType);
    }

    //注册EventProcesser
    void CEventProcesser::RegisterEventProcesser(const EU_EventType& euEventType, int iPriority)
    {
        m_pcEventRouter->RegisterEventHandler(euEventType, this, iPriority);
        m_setRegisteredEvent.insert(euEventType);
    }

    void CEventProcesser::CancelRegisterEventProcesser(const EU_EventType& euEventType, bool bErase)
    {
        if (m_pcEventRouter) {
            m_pcEventRouter->CancelRegisterEventHandler(euEventType, this);
            if (bErase) {
                if (m_setRegisteredEvent.count(euEventType))
                    m_setRegisteredEvent.erase(euEventType);
            }
        }
    }

    //发送Event
    void CEventProcesser::PostEvent(CEventPtr& pcEvent)
    {
        m_pcEventRouter->DispatchEvent(pcEvent);
    }

}
