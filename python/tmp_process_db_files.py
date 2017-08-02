# -*- coding:utf-8 -*-
# Create on 20170802
# Auth: wang.yijian
# Desc: 临时处理db文件


import json
import codecs
import mo_page_handler as mph



def tmp_process_black_list(db_file):
    movies = {}
    with codecs.open(db_file, 'r', 'utf-8') as f:
        movies = json.load(f)
    
    for sn in movies.keys():
        if 'genres' in movies[sn].keys():
            new_genres = []
            for genres in movies[sn]['genres']:
                if genres not in mph.series_black_list:
                    new_genres.append(genres)
            movies[sn]['genres'] = new_genres
    

    movies_json = json.dumps(movies, ensure_ascii=False, indent=2)
    with codecs.open('movies_fixed.json', 'w', 'utf-8') as f:
        f.write(movies_json)

tmp_process_black_list('D:\\Document\\MyDoc\\00.Dev\\Projects\\Others\\AMMS\\cpp\\build-amms-Qt5_6_2-Debug\\database\\movies_info.json')