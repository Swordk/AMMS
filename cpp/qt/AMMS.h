/////////////////////////////////////////////////////////////////////////﻿
///AMMS.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include "EventRouter.h"
#include "AMMSAppWindow.h"


namespace amms {

    class CAMMS : public CEventRouter {
	public:
		//构造函数
        CAMMS() {}

		//析构函数
        virtual ~CAMMS() {}
    public:
        //
        int Run(int argc, char *argv[]);

	private:
        //
        CAMMSAppWindow* m_pcAppWindow;
	};
}
