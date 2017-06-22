/////////////////////////////////////////////////////////////////////////﻿
///AMMS.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include <QApplication>
#include <QTextCodec>
#include <boost/date_time/gregorian/gregorian.hpp>
#include "AMMS.h"
#include "EventObject.h"

namespace amms {
    namespace bgg = boost::gregorian;

///启动
int CAMMS::Run(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置中文编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gb18030"));

    //Register
    qRegisterMetaType<CEventObject>("CEventObject");
    qRegisterMetaType<bgg::date>("boost_date");

    m_pcAppWindow = new CAMMSAppWindow(this);
    m_pcAppWindow->Init();

    return a.exec();
}

}
using namespace amms;
int main(int argc, char *argv[])
{
#ifdef WIN
    QCoreApplication::addLibraryPath("./qtplugins");
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    CAMMS* pcAmms = new CAMMS();
    return pcAmms->Run(argc, argv);
}
