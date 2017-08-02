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

    struct SMovieInfo {
        std::string             strSn;
        std::string             strTitle;
        std::string             strDate;
        std::string             strSeries;
        std::set<std::string>   setGenres;
        std::set<std::string>   setActors;
        std::string             strDirector;
        std::string             strProducer;
        std::string             strPublisher;
        int                     nMinutes;
    };

    struct SActorInfo {
        std::string             strName;
        std::string             strBirthDay;
        std::string             strCup;
        std::string             strHeight;
        std::string             strBust;
        std::string             strWaist;
        std::string             strHip;
        std::set<std::string>   setHobby;
    };


    class CMDataBase {
    public:
        static CMDataBase* GetInstance();
        void Init();


        inline SActorInfo ActorInfo(const std::string& strActorName) {
            return mapActors[strActorName];
        }

        inline SMovieInfo MovieInfo(const std::string& strMovieSn) {
            return mapMovies[strMovieSn];
        }


        inline size_t ActorMovieCount(const std::string& strActorName) {
            return mapActors2Sn[strActorName].size();
        }

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

        // inline std::map<std::string, std::map<std::string, std::set<std::string> > > Movies() const {
        //     return mapMovies;
        // }
        // inline std::map<std::string, std::set<std::string> > Movies(const std::string& strSn) const {
        //     if (mapMovies.count(strSn))
        //         return mapMovies.at(strSn);
        //     return std::map<std::string, std::set<std::string> >();
        // }

    private:
        CMDataBase()    {}
        void LoadMoviesInfo(const std::string& i_strDatabasePath);
        void LoadActorsInfo(const std::string& i_strDatabasePath);

        std::map<std::string, SMovieInfo>               mapMovies;
        std::map<std::string, SActorInfo>               mapActors;

        std::map<std::string, std::set<std::string> >   mapActors2Sn;
        std::map<std::string, std::set<std::string> >   mapGenres2Sn;
        std::map<std::string, std::set<std::string> >   mapProducers2Sn;
        std::map<std::string, std::set<std::string> >   mapPublisher2Sn;
        std::map<std::string, std::set<std::string> >   mapDirector2Sn;
        std::map<std::string, std::set<std::string> >   mapS2Sn;
        std::map<std::string, std::set<std::string> >   mapSeries2Sn;

    };

#define MDB CMDataBase::GetInstance
}
