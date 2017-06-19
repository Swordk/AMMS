# -*- coding:utf-8 -*-
# Create on 20170618
# Auth: wang.yijian
# Desc: 遍历db file 目录，生成相关文件 

import os
import codecs
import json
import db_src_file_parser as sf_parser

def walker(src_folder):
    movies_all = {}
    S_2_sn = {}
    genres_all = []
    genres_2_sn = {}
    actors_2_sn = {}
    series_2_sn = {}
    publisher_2_sn = {}
    producers_2_sn = {}

    files_all = os.listdir(src_folder)
    for src_file in files_all:
        # 不是 db src file
        if '.db' not in src_file:
            continue

        # print(src_file)
        movie_info = sf_parser.parse_db_source_file(src_folder + '/' + src_file)
        
        # 处理sn
        sn = movie_info['sn'][0]
        movies_all[sn] = movie_info
        
        # 处理S: ABP-001: S == ABP
        codes = sn.split('-')
        S = codes[0]
        if S not in S_2_sn.keys():
            S_2_sn[S] = []
        S_2_sn[S].append(sn)

        # 处理 genres
        genreses = movie_info['genres']
        genres_all.extend(genreses)
        for genres in genreses:
            if genres not in genres_2_sn.keys():
                genres_2_sn[genres] = []
            genres_2_sn[genres].append(sn)
        
        # 处理 actors
        actors = ['none']
        if 'actor' in movie_info.keys():
            actors = movie_info['actor']
        for actor in actors:
            if actor not in actors_2_sn.keys():
                actors_2_sn[actor] = []
            actors_2_sn[actor].append(sn)
        
        # 处理 series
        if 'series' in movie_info.keys():
            serieses = movie_info['series']
            for series in serieses:
                if series not in series_2_sn.keys():
                    series_2_sn[series] = []
                series_2_sn[series].append(sn)
        
        # 处理 publisher
        if 'publisher' in movie_info.keys():
            publishers =  movie_info['publisher']
            for publisher in publishers:
                if publisher not in publisher_2_sn.keys():
                    publisher_2_sn[publisher] = []
                publisher_2_sn[publisher].append(sn)
        
        # 处理 producers
        if 'producers' in movie_info.keys():
            producers = movie_info['producers']
            for producer in producers:
                if producer not in producers_2_sn.keys():
                    producers_2_sn[producer] = []
                producers_2_sn[producer].append(sn)



    movies_json = json.dumps(movies_all, ensure_ascii=False, indent=2)
    with codecs.open('movies.json', 'w', 'utf-8') as f:
        f.write(movies_json)
        
    S_2_sn_json = json.dumps(S_2_sn, ensure_ascii=False, indent=2)
    with codecs.open('S_2_sn.json', 'w', 'utf-8') as f:
        f.write(S_2_sn_json)

    genres_all_json = json.dumps(genres_all, ensure_ascii=False, indent=2)
    with codecs.open('genres_all.json', 'w', 'utf-8') as f:
        f.write(genres_all_json)

    genres_2_sn_json = json.dumps(genres_2_sn, ensure_ascii=False, indent=2)
    with codecs.open('genres_2_sn.json', 'w', 'utf-8') as f:
        f.write(genres_2_sn_json)

    actors_2_sn_json = json.dumps(actors_2_sn, ensure_ascii=False, indent=2)
    with codecs.open('actors_2_sn.json', 'w', 'utf-8') as f:
        f.write(actors_2_sn_json)

    series_2_sn_json = json.dumps(series_2_sn, ensure_ascii=False, indent=2)
    with codecs.open('series_2_sn.json', 'w', 'utf-8') as f:
        f.write(series_2_sn_json)

    publisher_2_sn_json = json.dumps(publisher_2_sn, ensure_ascii=False, indent=2)
    with codecs.open('publisher_2_sndata.json', 'w', 'utf-8') as f:
        f.write(publisher_2_sn_json)

    producers_2_sn_json = json.dumps(producers_2_sn, ensure_ascii=False, indent=2)
    with codecs.open('producers_2_sn.json', 'w', 'utf-8') as f:
        f.write(producers_2_sn_json)

# json.dumps(['foo', {'bar': ('baz', None, 1.0, 2)}], 'test.json')
walker('db/src')