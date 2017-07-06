/////////////////////////////////////////////////////////////////////////﻿
///Config
///20160925 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#include "Config.h"
#include <sstream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace amms {

    class CFileConfig : public CConfig {
    public:

        explicit CFileConfig(const std::string& strFileName)
            : m_strFileName(strFileName)
        {}
        virtual ~CFileConfig()  {}

    public:
        virtual void Init() override;

    protected:
        std::string m_strFileName;
    };

    void CFileConfig::Init()
    {
        std::ifstream ifs(m_strFileName);
        if (!ifs)
            return;

        std::stringstream ssBuffer;
        ssBuffer << ifs.rdbuf();

        rapidjson::Document doc;
        doc.Parse(ssBuffer.str().c_str());

        if (doc.IsObject() == false)
            return;

        for (auto itKey = doc.MemberBegin(); itKey != doc.MemberEnd(); ++itKey) {
            std::string strKey = itKey->name.GetString();
            for (auto itItem = itKey->value.MemberBegin();
                itItem != itKey->value.MemberEnd(); ++itItem)
            {
                std::string strItem = itItem->name.GetString();
                if (strKey == "Database") {
                    if (strItem == "db_path") {
                        m_strDbPath = itItem->value.GetString();
                    }
                }
                else if (strKey == "Movie") {
                    if (strItem == "movie_path") {
                        m_strMoviePath = itItem->value.GetString();
                    }
                    else if (strItem == "movie_file_extension") {

                        for (auto& itExt : itItem->value.GetArray()) {
                            std::string strExt = itExt.GetString();
                            m_setMovieFileExtension.insert(strExt);
                        }
                    }
                }
                else if (strKey == "UI") {
                    if (strItem == "movie_wall") {
                        for (auto itItem2 = itItem->value.MemberBegin();
                            itItem2 != itItem->value.MemberEnd(); ++itItem2)
                        {
                            std::string strItem2 = itItem2->name.GetString();
                            if (strItem2 == "movie_frame") {
                                for (auto itItem3 = itItem2->value.MemberBegin();
                                     itItem3 != itItem2->value.MemberEnd(); ++itItem3)
                                {
                                    std::string strItem3 = itItem3->name.GetString();
                                    if (strItem3 == "width") {
                                        m_nMovieFrameWidth = atoi(itItem3->value.GetString());
                                    }
                                    else if (strItem3 == "height") {
                                        m_nMovieFrameHeight = atoi(itItem3->value.GetString());
                                    }
                                }
                            }

                        }
                    }
                }
                else if (strKey == "Player") {
                    if (strItem == "player_path")
                        m_strPlayerPath = itItem->value.GetString();
                }
            }
        }
    }


    //////////////////////////////////////////////////////////////////////
    class CConfigImp : public CConfig {
    public:
        explicit CConfigImp()
            : defaultConfig("DefaultConfig.json")
            , userConfig("UserConfig.json")
        {}
        virtual ~CConfigImp()   {}

        virtual void Init() override;
        virtual inline std::string DbPath() const override {
            std::string strConfig = userConfig.DbPath();
            if (strConfig == "")
                strConfig = defaultConfig.DbPath();
            return strConfig;
        }
        virtual inline std::string MoviePath() const override {
            std::string strConfig = userConfig.MoviePath();
            if (strConfig == "")
                strConfig = defaultConfig.MoviePath();
            return strConfig;
        }
        virtual inline std::set<std::string> MovieFileExtension() const override {
            std::set<std::string> setConfig = userConfig.MovieFileExtension();
            if (setConfig.empty())
                setConfig = defaultConfig.MovieFileExtension();
            return setConfig;
        }
        virtual inline int MovieFrameWidth() const override {
            int nConfig = userConfig.MovieFrameWidth();
            if (nConfig == 0)
                nConfig = defaultConfig.MovieFrameWidth();
            return nConfig;
        }
        virtual inline int MovieFrameHeight() const override {
            int nConfig = userConfig.MovieFrameHeight();
            if (nConfig == 0)
                nConfig = defaultConfig.MovieFrameHeight();
            return nConfig;
        }

    protected:
        CFileConfig defaultConfig;
        CFileConfig userConfig;
    };

    void CConfigImp::Init()
    {
        defaultConfig.Init();
        userConfig.Init();
    }

    //////////////////////////////////////////////////////////////////////
    CConfig* CConfig::GetInstance()
    {
        static CConfigImp* pcConfig = new CConfigImp();
        return pcConfig;
    }
}

