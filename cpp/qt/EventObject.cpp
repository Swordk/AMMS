/////////////////////////////////////////////////////////////////////////﻿
///EventObject.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "EventObject.h"

namespace amms {
    CEventObject::CEventObject()
        : QObject(NULL)
    {}

    CEventObject::CEventObject(const CEventObject &other)
        : QObject(NULL), m_pcEvent(other.m_pcEvent)
    {}

    CEventObject::CEventObject(CEventPtr v_pcEvent)
        : QObject(NULL), m_pcEvent(v_pcEvent)
    {}
}
