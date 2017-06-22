/////////////////////////////////////////////////////////////////////////
///EventProcesser.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <queue>
#include <set>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "Event.h"
#include "EventRouter.h"

namespace amms {
    class CEventRouter;     // External class 
    class CEventProcesser;

    // -------------------------------------------------------------------
    //Event异步处理函数
    void AsyncProcessEvent(CEventProcesser *pcEventProcesser);

    class CEventProcesser {
    public:
        //构造函数
        explicit CEventProcesser(bool bIsSynchronized, CEventRouter* pcEventRouter);
        virtual ~CEventProcesser()  {}
    public:
        inline bool IsStoped() { return m_bIsStoped; }

        //循环处理，异步处理时使用
        void AsyncLoop();

        //处理Event
        inline void ProcessEvent(CEventPtr& pcEvent) {
            if (m_bIsSynchronized) {
                _ProcessEvent(pcEvent);
            }
            else {
                m_mtxEvents.lock();
                m_queueEvents.push(pcEvent);
                m_mtxEvents.unlock();

                m_condEvents.notify_one();	//通知异步处理线程
            }
        }


    ///子类重载方法
    protected:
        //
        virtual void _ProcessEvent(CEventPtr& pcEvent) = 0;
    
        ///子类调用方法
    protected:
        //注册EventProcesser
        void RegisterEventProcesser(const EU_EventType& euEventType);
        void RegisterEventProcesser(const EU_EventType& euEventType, int iPriority);

        void CancelRegisterEventProcesser(const EU_EventType& euEventType, bool bErase = false);

        //发送Event
        void PostEvent(CEventPtr& pcEvent);

    protected:
        CEventRouter*   m_pcEventRouter;
    
    private:
        //处理方式是否同步
        bool m_bIsSynchronized;

        std::queue<CEventPtr> m_queueEvents;             //异步处理时使用的Event队列
        boost::mutex m_mtxEvents;                   //队列操作互斥锁
        boost::condition_variable_any m_condEvents; //条件变量
        boost::mutex m_mtxCondEvents;               //条件变量使用的mutex

        bool m_bRunningFlag;
        bool m_bIsStoped;

        std::set<EU_EventType>   m_setRegisteredEvent;
    };
}

