#-------------------------------------------------
#
# Project created by QtCreator 2017-06-22T11:07:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = amms
TEMPLATE = app
RC_ICONS = amms2.ico

SOURCES += \
    Config.cpp \
    MDataBase.cpp \
    EventProcesser.cpp \
    EventRouter.cpp \
    EventObject.cpp \
    TableWidget.cpp \
    ActorsListWidget.cpp \
    CommonContentListWidget.cpp \
    ActorInfoWidget.cpp \
    MovieWallWidget.cpp \
    MovieWallSortCtlWidget.cpp \
    MovieInfoWindow.cpp \
    AMMSAppWindow.cpp \
    PicCache.cpp \
    PicLoader.cpp \
    ScanDiskProcesser.cpp \
    AMMS.cpp

HEADERS  += \
    Config.h \
    MDataBase.h \
    Typedef.h \
    Event.h \
    EventProcesser.h \
    EventRouter.h \
    EventObject.h \
    TableWidget.h \
    ActorsListWidget.h \
    CommonContentListWidget.h \
    ActorInfoWidget.h \
    MovieWallWidget.h \
    MovieWallSortCtlWidget.h \
    MovieInfoWindow.h \
    AMMSAppWindow.h \
    PicCache.h \
    PicLoader.h \
    ScanDiskProcesser.h \
    AMMS.h


win32 {
    RC_FILE += ammsVersion.rc
    BOOST_VERSION = 1_61
    IS_DEBUG=-gd
    BOOST_DIR = C:/boost/boost_$${BOOST_VERSION}_0
    BOOST_LIB_DIR = $${BOOST_DIR}/stage/lib
    LIBS += -l$${BOOST_LIB_DIR}/libboost_atomic-vc120-mt$${IS_DEBUG}-$${BOOST_VERSION} \
            -l$${BOOST_LIB_DIR}/libboost_locale-vc120-mt$${IS_DEBUG}-$${BOOST_VERSION} \
            -l$${BOOST_LIB_DIR}/libboost_date_time-vc120-mt$${IS_DEBUG}-$${BOOST_VERSION} \
            -l$${BOOST_LIB_DIR}/libboost_thread-vc120-mt$${IS_DEBUG}-$${BOOST_VERSION} \
            -l$${BOOST_LIB_DIR}/libboost_system-vc120-mt$${IS_DEBUG}-$${BOOST_VERSION} \
            -l$${BOOST_LIB_DIR}/libboost_chrono-vc120-mt$${IS_DEBUG}-$${BOOST_VERSION}

    INCLUDEPATH += $${BOOST_DIR}
    DEFINES += WIN
}

CONFIG += c++11

DISTFILES += \
    Config.xml


