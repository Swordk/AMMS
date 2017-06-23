/////////////////////////////////////////////////////////////////////////﻿
///MDataBase
///20160919 jason wong 创建该文件
///Movie 数据库
/////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <map>
#include <set>

namespace amms {

    class CMDataBase {
    public:
        static CMDataBase* GetInstance();
        void Init();

        inline std::map<std::string, std::set<std::string> > Actors2Sn() const {
            return mapActors2Sn;
        }
        inline std::set<std::string> Actors2Sn(const std::string& strActor) const {
            if (mapActors2Sn.count(strActor) > 0)
                return mapActors2Sn.at(strActor);
            return std::set<std::string>();
        }

        inline std::map<std::string, std::set<std::string> > Genres2Sn() const {
            return mapGenres2Sn;
        }
        inline std::set<std::string> Genres2Sn(const std::string& strGenres) const {
            if (mapGenres2Sn.count(strGenres) > 0)
                return mapGenres2Sn.at(strGenres);
            return std::set<std::string>();
        }

        inline std::map<std::string, std::set<std::string> > Producers2Sn() const {
            return mapProducers2Sn;
        }
        inline std::set<std::string> Producers2Sn(const std::string& strProducer) const {
            if (mapProducers2Sn.count(strProducer))
                return mapProducers2Sn.at(strProducer);
            return std::set<std::string>();
        }

        inline std::map<std::string, std::set<std::string> > Publisher2Sn() const {
            return mapPublisher2Sn;
        }
        inline std::set<std::string> Publisher2Sn(const std::string& strPublisher) const {
            if (mapPublisher2Sn.count(strPublisher))
                return mapPublisher2Sn.at(strPublisher);
            return std::set<std::string>();
        }

        inline std::map<std::string, std::set<std::string> > S2Sn() const {
            return mapS2Sn;
        }
        inline std::set<std::string> S2Sn(const std::string& strS) const {
            if (mapS2Sn.count(strS))
                return mapS2Sn.at(strS);
            return std::set<std::string>();
        }

        inline std::map<std::string, std::set<std::string> > Series2Sn() const {
            return mapSeries2Sn;
        }

        inline std::set<std::string> Series2Sn(const std::string& strSeries) const {
            if (mapSeries2Sn.count(strSeries))
                return mapSeries2Sn.at(strSeries);
            return std::set<std::string>();
        }

        inline std::map<std::string, std::map<std::string, std::set<std::string> > > Movies() const {
            return mapMovies;
        }
        inline std::map<std::string, std::set<std::string> > Movies(const std::string& strSn) const {
            if (mapMovies.count(strSn))
                return mapMovies.at(strSn);
            return std::map<std::string, std::set<std::string> >();
        }

    private:
        CMDataBase()    {}

        std::map<std::string, std::set<std::string> > mapActors2Sn;
        std::map<std::string, std::set<std::string> > mapGenres2Sn;
        std::map<std::string, std::set<std::string> > mapProducers2Sn;
        std::map<std::string, std::set<std::string> > mapPublisher2Sn;
        std::map<std::string, std::set<std::string> > mapS2Sn;
        std::map<std::string, std::set<std::string> > mapSeries2Sn;
        // sn->item->content
        std::map<std::string, std::map<std::string, std::set<std::string> > > mapMovies;
    };

#define MDB CMDataBase::GetInstance
}
