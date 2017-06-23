/////////////////////////////////////////////////////////////////////////﻿
///AMMS.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include <QElapsedTimer>

#include <boost/date_time/gregorian/gregorian.hpp>
#include "AMMS.h"
#include "MDataBase.h"
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

    QSplashScreen splash(QPixmap("D:/Documents/Doc/01.Dev/Projects/Others/AMMS/cpp/qt/amms.png"));
    splash.setDisabled(true); //禁用用户的输入事件响应
    splash.show();
    splash.showMessage(QStringLiteral("内存数据库管理器.加载模块数据.正在启动中...."),
        Qt::AlignLeft|Qt::AlignBottom,Qt::black);
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<2000)
    {
        QCoreApplication::processEvents();
    }

    //同时创建主视图对象
    // MainWindow w;
    splash.showMessage(QStringLiteral("AMMS, 您的私人电影数据库"),Qt::AlignLeft|Qt::AlignBottom,Qt::black);
    //预加载程序数据;
    // loadModulesData();
    MDB()->Init();
    //程序数据加载完毕后， 显示主视图，并结束启动画面
    // w.show();

    //QElapsedTimer t;
    t.restart();
    while(t.elapsed()<3000)
    {
        QCoreApplication::processEvents();
    }

    m_pcAppWindow = new CAMMSAppWindow(this);
    m_pcAppWindow->Init();

    splash.finish(m_pcAppWindow);

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
