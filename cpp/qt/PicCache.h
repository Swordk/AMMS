/////////////////////////////////////////////////////////////////////////﻿
///PicCache.h
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <map>
#include <QPixmap>
#include <boost/thread/shared_mutex.hpp>
#include "Typedef.h"
#include "Event.h"
#include "EventProcesser.h"


namespace amms {
    using namespace std;

    class CPicCache {
    public:
        static CPicCache* GetInstance();
        virtual ~CPicCache(){}

    public:
        bool LoadPixmap(const string& strFileName);

        bool GetPixmap(const string& strFileName, QPixmap& o_pix);
        inline bool HasPixmap(const string& strFileName) {
            readLock rl(m_mtxPixmap);
            return m_mapPixmap.count(strFileName) > 0;
        }

    private:
        CPicCache(){}

        map<string, QPixmap>    m_mapPixmap;
        boost::shared_mutex     m_mtxPixmap;

    };


#define PicCacheInst() CPicCache::GetInstance()
}
