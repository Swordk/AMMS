/////////////////////////////////////////////////////////////////////////﻿
///Config
///20160925 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <map>


namespace amms {

    class CConfig {
    public:
        static CConfig* GetInstance();
        virtual ~CConfig(){}

        virtual void Init() = 0;
        virtual inline std::string strDbPath() const    { return m_strDbPath;   }
        virtual inline std::string strMoviePath() const { return m_strMoviePath;    }
        virtual inline int nMovieFrameWidth() const     { return m_nMovieFrameWidth;    }
        virtual inline int nMovieFrameHeight() const    { return m_nMovieFrameHeight;   }

    protected:
        explicit CConfig()
            : m_strDbPath("database")
            , m_strMoviePath("")
            , m_nMovieFrameWidth(510)
            , m_nMovieFrameHeight(350)
        {}

        std::string m_strDbPath;
        std::string m_strMoviePath;
        int         m_nMovieFrameWidth;
        int         m_nMovieFrameHeight;
    };
#define CFG CConfig::GetInstance
}
