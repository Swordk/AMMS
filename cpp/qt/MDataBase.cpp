/////////////////////////////////////////////////////////////////////////﻿
///MDataBase
///20160919 jason wong 创建该文件
///Movie 数据库
/////////////////////////////////////////////////////////////////////////

#include "MDataBase.h"
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

namespace amms {
    class CJsonFileHandler {
    public:
        CJsonFileHandler(){}
        ~CJsonFileHandler(){}

    public:
        static std::string LoadFile(const std::string& strFileName) {
            std::ifstream ifs(strFileName);
            std::stringstream ssBuffer;
            ssBuffer << ifs.rdbuf();
            return ssBuffer.str();
        }

        //
        static bool LoadKey2List(const std::string& i_strFileName,
            std::map<std::string, std::set<std::string> >& o_mapData) {
            std::string strContents = LoadFile(i_strFileName);
            rapidjson::Document doc;
            doc.Parse(strContents.c_str());
            if (doc.IsObject() == false)
                return false;

            o_mapData.clear();
            for (auto itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr) {
                std::string strKey = itr->name.GetString();
                for (auto& itValue : itr->value.GetArray()) {
                    std::string strValue = itValue.GetString();
                    o_mapData[strKey].insert(strValue);
                }
            }
            return true;
        }

        //
        static bool LoadKey2Key2List(const std::string& i_strFileName,
            std::map<std::string, std::map<std::string, std::set<std::string> > >& o_mapData) {
            std::string strContents = LoadFile(i_strFileName);
            rapidjson::Document doc;
            doc.Parse(strContents.c_str());
            if (doc.IsObject() == false)
                return false;

            o_mapData.clear();
            for (auto itKey1 = doc.MemberBegin(); itKey1 != doc.MemberEnd(); ++itKey1) {
                std::string strKey1 = itKey1->name.GetString();
                for (auto itKey2 = itKey1->value.MemberBegin(); itKey2 != itKey1->value.MemberEnd(); ++itKey2) {
                    std::string strKey2 = itKey2->name.GetString();
                    for (auto& itValue : itKey2->value.GetArray()) {
                        o_mapData[strKey1][strKey2].insert(itValue.GetString());
                    }
                }
            }
            return true;
        }
    };

    #define LoadActors2Sn(mapActors2Sn)         CJsonFileHandler::LoadKey2List("database/actors_2_sn.json", mapActors2Sn)
    #define LoadGenres2Sn(mapGenres2Sn)         CJsonFileHandler::LoadKey2List("database/genres_2_sn.json", mapGenres2Sn)
    #define LoadProducers2Sn(mapProducers2Sn)   CJsonFileHandler::LoadKey2List("database/producers_2_sn.json", mapProducers2Sn)
    #define LoadPublisher2Sn(mapPublisher2Sn)   CJsonFileHandler::LoadKey2List("database/publisher_2_sn.json", mapPublisher2Sn)
    #define LoadS2Sn(mapS2Sn)                   CJsonFileHandler::LoadKey2List("database/S_2_sn.json", mapS2Sn)
    #define LaodSeries2Sn(mapSeries2Sn)         CJsonFileHandler::LoadKey2List("database/series_2_sn.json", mapSeries2Sn)
    #define LoadMovies(mapMovies)               CJsonFileHandler::LoadKey2Key2List("database/movies.json", mapMovies)
}


namespace amms {
    CMDataBase* CMDataBase::GetInstance()
    {
        static CMDataBase s_instance;
        return &s_instance;
    }

    void CMDataBase::Init()
    {
        bool bRtn = LoadActors2Sn(mapActors2Sn);

        bRtn = LoadGenres2Sn(mapGenres2Sn);

        bRtn = LoadProducers2Sn(mapProducers2Sn);

        bRtn = LoadPublisher2Sn(mapPublisher2Sn);

        bRtn = LoadS2Sn(mapS2Sn);

        bRtn = LaodSeries2Sn(mapSeries2Sn);

        bRtn = LoadMovies(mapMovies);
    }

}
