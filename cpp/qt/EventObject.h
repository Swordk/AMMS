/////////////////////////////////////////////////////////////////////////
///EventObject.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <QObject>
#include "Event.h"

namespace amms {

    class CEventObject : public QObject {
        Q_OBJECT
    public:
        //构造函数
        explicit CEventObject();
        CEventObject(const CEventObject &other);
        CEventObject(CEventPtr v_pcEvent);

        //析构函数
        ~CEventObject() {}

        //
        CEventPtr GetEvent() {
            return m_pcEvent;
        }

    signals:

    public slots:

    private:
        //
        CEventPtr m_pcEvent;
    };
}
