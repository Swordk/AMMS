/////////////////////////////////////////////////////////////////////////
///EventRouter.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <map>
#include "Event.h"
#include "EventProcesser.h"

namespace amms {
    class CEventProcesser;  // External class 
    class CEventRouter;

    // -------------------------------------------------------------------
    enum EU_EventProcesserPriority {
        eppHighest = 0,
        eppHigher = 10,
        eppNormal = 20,
        eppLower = 30,
        eppLowest = 40
    };

    typedef struct stEventProcesserNode {
        CEventProcesser *m_pcProcesser;
        int m_iPriority;

        bool operator < (const struct stEventProcesserNode &a) const {
            return m_iPriority < a.m_iPriority;
        }
    } EventProcesserNode_ST;

    class CEventRouter {
    public:
        //构造函数
        explicit CEventRouter() {}

        //析构函数
        virtual ~CEventRouter() {}

    public:
        //注册EventHandler
        void RegisterEventHandler(const EU_EventType& v_euEventType, CEventProcesser* v_pcEventProcesser, int v_iPriority);

        //注销EventHandler
        void CancelRegisterEventHandler(const EU_EventType& v_euEventType, CEventProcesser* v_pcEventProcesser);

        //发送Event
        void DispatchEvent(CEventPtr& v_pcEvent);

    private:
        //所有EventHandler
        std::map<EU_EventType, std::vector<EventProcesserNode_ST> > m_mapProcessers;
        boost::shared_mutex m_mtxProcessers;
    };
}
