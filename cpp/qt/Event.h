/////////////////////////////////////////////////////////////////////////
///Event.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////


#pragma once

#include <string>
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
    class CLoadPicReqEvent;
    class CLoadPicRspEvent;

    // -------------------------------------------------------------------
    enum EU_EventType {
        etStopEventProcesser = 0,
        etReqLoadPic,
        etRspLoadPic
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



    //////////////////////////////////////////////////////////////////////////
    class CLoadPicReqEvent : public CEvent {
    public:
        explicit CLoadPicReqEvent(std::string strFileName)
            : CEvent(etReqLoadPic)
            , m_strFileName(strFileName)
        {}

        virtual ~CLoadPicReqEvent(){}

    public:
        std::string m_strFileName;
    };


    class CLoadPicRspEvent : public CLoadPicReqEvent {
    public:
        explicit CLoadPicRspEvent(std::string strFileName, bool bSuccess)
            : CLoadPicReqEvent(strFileName)
            , m_bSuccess(bSuccess)
        {
            m_euType = etRspLoadPic;
        }

    public:
        bool m_bSuccess;

    };


    // BOOST_SERIALIZATION_ASSUME_ABSTRACT(CEvent)
    typedef boost::shared_ptr<CEvent> CEventPtr;
}
