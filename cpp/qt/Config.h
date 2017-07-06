/////////////////////////////////////////////////////////////////////////﻿
///Config
///20160925 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <set>
#include <map>


namespace amms {

    class CConfig {
    public:
        static CConfig* GetInstance();
        virtual ~CConfig(){}

        virtual void Init() = 0;
        virtual inline std::string DbPath() const                       { return m_strDbPath;   }
        virtual inline std::string MoviePath() const                    { return m_strMoviePath;    }
        virtual inline std::set<std::string> MovieFileExtension() const { return m_setMovieFileExtension; }
        virtual inline int MovieFrameWidth() const                      { return m_nMovieFrameWidth;    }
        virtual inline int MovieFrameHeight() const                     { return m_nMovieFrameHeight;   }
        virtual inline std::string PlayerPath() const                   { return m_strPlayerPath; }

    protected:
        explicit CConfig()
            : m_strDbPath("database")
            , m_strMoviePath("")
            , m_setMovieFileExtension()
            , m_nMovieFrameWidth(510)
            , m_nMovieFrameHeight(350)
        {}

        std::string m_strDbPath;
        std::string m_strMoviePath;
        std::set<std::string>   m_setMovieFileExtension;
        int         m_nMovieFrameWidth;
        int         m_nMovieFrameHeight;
        std::string m_strPlayerPath;
    };
#define CFG CConfig::GetInstance
}
