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
    class CPicCache {
    public:
        static CPicCache* GetInstance();
        virtual ~CPicCache(){}

    public:
        bool LoadPixmap(const std::string& strFileName);

        bool GetPixmap(const std::string& strFileName, QPixmap& o_pix);
        inline bool HasPixmap(const std::string& strFileName) {
            readLock rl(m_mtxPixmap);
            return m_mapPixmap.count(strFileName) > 0;
        }

    private:
        CPicCache(){}

        std::map<std::string, QPixmap>    m_mapPixmap;
        boost::shared_mutex     m_mtxPixmap;

    };


#define PicCacheInst() CPicCache::GetInstance()
}
