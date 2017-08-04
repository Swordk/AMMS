/////////////////////////////////////////////////////////////////////////﻿
///PicCache.cpp
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "PicCache.h"
#include <QFileInfo>

namespace amms {
    CPicCache* CPicCache::GetInstance()
    {
        static CPicCache s_instance;
        return &s_instance;
    }

    bool CPicCache::LoadPixmap(const std::string& strFileName)
    {
        readLock rl(m_mtxPixmap);
        if (m_mapPixmap.count(strFileName))
            return true;
        rl.unlock();

        QFileInfo file(strFileName.c_str());
        if (file.exists() == false)
            return false;
        writeLock wl(m_mtxPixmap);
        m_mapPixmap[strFileName] = QPixmap(strFileName.c_str());
        return true;
    }

    bool CPicCache::GetPixmap(const std::string &strFileName, QPixmap &o_pix)
    {
        readLock rl(m_mtxPixmap);
        if (m_mapPixmap.count(strFileName) <= 0)
            return false;
        o_pix = m_mapPixmap[strFileName];
        return true;
    }

}
