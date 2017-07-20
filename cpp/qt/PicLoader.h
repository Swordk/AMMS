/////////////////////////////////////////////////////////////////////////﻿
///PicLoader.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Event.h"
#include "EventProcesser.h"

namespace amms {

    class CPicLoader : public CEventProcesser {
    public:
        explicit CPicLoader(CEventRouter* pcRouter)
            : CEventProcesser(false, pcRouter)
        {}
        virtual ~CPicLoader(){}

        void Init();

    protected:
        //
        virtual void _ProcessEvent(CEventPtr& pcEvent) override;


    };

}
