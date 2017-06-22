/////////////////////////////////////////////////////////////////////////
///Event.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////


#pragma once

#include <boost/shared_ptr.hpp>
// #include <boost/serialization/nvp.hpp>
// #include <boost/serialization/access.hpp>
// #include <boost/serialization/base_object.hpp>
// #include <boost/serialization/export.hpp>
// #include <boost/serialization/shared_ptr.hpp>
// #include <boost/serialization/vector.hpp>
// #include <boost/serialization/string.hpp>

namespace amms {

    class CEvent;

    // -------------------------------------------------------------------
    enum EU_EventType {
        etStopEventProcesser = 0
    };

    //////////////////////////////////////////////////////////////////////////
    // Event 基类
    class CEvent {
    public:
        explicit CEvent()    {}
        explicit CEvent(const EU_EventType& euType)
            : m_euType(euType), m_iSessionId(0)
        {}

        virtual ~CEvent()   {}
    public:
        inline EU_EventType Type() const { 
            return m_euType; 
        }        
        inline int SessionId() const {
            return m_iSessionId;
        }

        inline void SessionId(int val) {
            m_iSessionId = val;
        }

    protected:
        //Event类型
        EU_EventType m_euType;
        int m_iSessionId;
    };

    // BOOST_SERIALIZATION_ASSUME_ABSTRACT(CEvent)
    typedef boost::shared_ptr<CEvent> CEventPtr;
}
