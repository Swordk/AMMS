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
#include "Config.h"

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

    #define LoadActors2Sn(mapActors2Sn)         CJsonFileHandler::LoadKey2List(CFG()->strDbPath() + "\\actors_2_sn.json", mapActors2Sn)
    #define LoadGenres2Sn(mapGenres2Sn)         CJsonFileHandler::LoadKey2List(CFG()->strDbPath() + "\\genres_2_sn.json", mapGenres2Sn)
    #define LoadProducers2Sn(mapProducers2Sn)   CJsonFileHandler::LoadKey2List(CFG()->strDbPath() + "\\producers_2_sn.json", mapProducers2Sn)
    #define LoadPublisher2Sn(mapPublisher2Sn)   CJsonFileHandler::LoadKey2List(CFG()->strDbPath() + "\\publisher_2_sn.json", mapPublisher2Sn)
    #define LoadS2Sn(mapS2Sn)                   CJsonFileHandler::LoadKey2List(CFG()->strDbPath() + "\\S_2_sn.json", mapS2Sn)
    #define LaodSeries2Sn(mapSeries2Sn)         CJsonFileHandler::LoadKey2List(CFG()->strDbPath() + "\\series_2_sn.json", mapSeries2Sn)
    #define LoadMovies(mapMovies)               CJsonFileHandler::LoadKey2Key2List(CFG()->strDbPath() + "\\movies.json", mapMovies)
}


namespace amms {
    void LoadMoviesInfo();

    CMDataBase* CMDataBase::GetInstance()
    {
        static CMDataBase s_instance;
        return &s_instance;
    }


    void CMDataBase::Init()
    {
        std::string strDbPath = CFG()->strDbPath();
        LoadMoviesInfo(strDbPath);
        LoadActorsInfo(strDbPath);
        bool bRtn = LoadActors2Sn(mapActors2Sn);

        bRtn = LoadGenres2Sn(mapGenres2Sn);

        bRtn = LoadProducers2Sn(mapProducers2Sn);

        bRtn = LoadPublisher2Sn(mapPublisher2Sn);

        bRtn = LoadS2Sn(mapS2Sn);

        bRtn = LaodSeries2Sn(mapSeries2Sn);

        // bRtn = LoadMovies(mapMovies);
    }

    void CMDataBase::LoadActorsInfo(const std::string& i_strDatabasePath)
    {
        std::string strActorFile = i_strDatabasePath + "\\actors_info.json";
        std::string strContents = CJsonFileHandler::LoadFile(strActorFile);
        rapidjson::Document doc;
        doc.Parse(strContents.c_str());
        if (doc.IsObject() == false)
            return;

        for (auto& itActor = doc.MemberBegin(); itActor != doc.MemberEnd(); ++itActor) {
            std::string strName = itActor->name.GetString();
            SActorInfo& actorInfo = mapActors[strName];
            actorInfo.strName = strName;
            for (auto& itKey = itActor->value.MemberBegin(); itKey != itActor->value.MemberEnd(); ++itKey) {
                std::string strKey = itKey->name.GetString();
                if (strKey == "birth_day") {
                    actorInfo.strBirthDay = itKey->value.GetString();
                }
                else if (strKey == "height") {
                    actorInfo.strHeight = itKey->value.GetString();
                }
                else if (strKey == "cup") {
                    actorInfo.strCup = itKey->value.GetString();
                }
                else if (strKey == "bust") {
                    actorInfo.strBust = itKey->value.GetString();
                }
                else if (strKey == "waist") {
                    actorInfo.strWaist = itKey->value.GetString();
                }
                else if (strKey == "hip") {
                    actorInfo.strHip = itKey->value.GetString();
                }
                else if (strKey == "hobby") {
                    for (auto& itHobby : itKey->value.GetArray()) {
                        actorInfo.setHobby.insert(itHobby.GetString());
                    }
                }
            }
        }
    }

    void CMDataBase::LoadMoviesInfo(const std::string& i_strDatabasePath)
    {
        std::string strMovieFile = i_strDatabasePath + "\\movies_info.json";
        std::string strContents = CJsonFileHandler::LoadFile(strMovieFile);
        rapidjson::Document doc;
        doc.Parse(strContents.c_str());
        if (doc.IsObject() == false)
            return;

        // o_mapData.clear();

        for (auto& itSn = doc.MemberBegin(); itSn != doc.MemberEnd(); ++itSn) {
            std::string strSn = itSn->name.GetString();
            SMovieInfo& movieInfo = mapMovies[strSn];
            movieInfo.strSn = strSn;

            for (auto& itKey = itSn->value.MemberBegin(); itKey != itSn->value.MemberEnd(); ++itKey) {
                std::string strKey = itKey->name.GetString();
                if (strKey == "title") {
                    movieInfo.strTitle = itKey->value.GetString();
                }
                else if (strKey == "actors") {
                    for (auto& itValue : itKey->value.GetArray()) {
                        std::string strActor = itValue.GetString();
                        movieInfo.setActors.insert(strActor);
                        mapActors2Sn[strActor].insert(strSn);
                    }
                }
                else if (strKey == "genres") {
                    for (auto& itValue : itKey->value.GetArray()) {
                        std::string strGenres = itValue.GetString();
                        movieInfo.setGenres.insert(strGenres);
                        mapGenres2Sn[strGenres].insert(strSn);
                    }
                }
                else if (strKey == "movie_time") {
                    std::string strMinutes = itKey->value.GetString();
                    int nlen = strMinutes.length();
                    strMinutes = strMinutes.substr(0, nlen-6);
                    movieInfo.nMinutes = stoi(strMinutes);
                }
                else if (strKey == "director") {
                    std::string strDirector = itKey->value.GetString();
                    movieInfo.strDirector = strDirector;
                    mapDirector2Sn[strDirector].insert(strSn);
                }
                else if (strKey == "producers") {
                    std::string strProducer = itKey->value.GetString();
                    movieInfo.strProducer = strProducer;
                    mapProducers2Sn[strProducer].insert(strSn);
                }
                else if (strKey == "publisher") {
                    std::string strPublisher = itKey->value.GetString();
                    movieInfo.strPublisher = strPublisher;
                    mapPublisher2Sn[strPublisher].insert(strSn);
                }
                else if (strKey == "date") {
                    std::string strDate = itKey->value.GetString();
                    movieInfo.strDate = strDate;
                }
            }
        }
        return;
    }
}
