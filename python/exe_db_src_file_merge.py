# -*- coding:utf-8 -*-
# Create on 20170618
# Auth: wang.yijian
# Desc: db src 文件 合成

import os
import sys
import json
import codecs



def process(movie_path):
    pass


if __name__ == '__main__':
    movie_path = './'
    if len(sys.argv) > 2:
        print('Usage:')
        print('    ' + sys.argv[0] + ' movie_path')
        exit(1)
    if len(sys.argv) == 2:
        movie_path = sys.argv[1] + '/'
    
    movie_path = 'X:\\SublimeText3\\Data\\d\\2\\00.done\\0'
    print(movie_path)

    dict_movies_info_all = {}
    dict_actors_info_all = {}
    dict_movies_pics_all = {}
    folders_all = os.listdir(movie_path)
    for folder in sorted(folders_all):
        folder = movie_path + "/" + folder
        print(folder)
        if os.path.isdir(folder):
            with codecs.open(folder + '/movies.json', 'r', 'utf-8') as f:
                movies = json.load(f)
                dict_movies_info_all.update(movies)
            with codecs.open(folder + '/actors.json', 'r', 'utf-8') as f:
                actors = json.load(f)
                dict_actors_info_all.update(actors)
            with codecs.open(folder + '/pics.json', 'r', 'utf-8') as f:
                pics = json.load(f)
                dict_movies_pics_all.update(pics)

    movies_json = json.dumps(dict_movies_info_all, ensure_ascii=False, indent=2)
    with codecs.open('movies.json', 'w', 'utf-8') as f:
        f.write(movies_json)
    
    actors_json = json.dumps(dict_actors_info_all, ensure_ascii=False, indent=2)
    with codecs.open('actors.json', 'w', 'utf-8') as f:
        f.write(actors_json)

    pics_json = json.dumps(dict_movies_pics_all, ensure_ascii=False, indent=2)
    with codecs.open('pics.json', 'w', 'utf-8') as f:
        f.write(pics_json)
    print('done')
    