# -*- coding:utf-8 -*-
# Create on 20170620
# Auth: wang.yijian
# Desc: 合并json

import codecs
import json

def dict_merge(dict1, dict2):
    dict1.update(dict2)
    return dict1
    

def dict_not_in(dict1, dict2):
    '''
    @return: elems of dict2 not in dict1
    '''
    rtn_dict = {}
    for key in dict2.keys():
        if key not in dict1.keys():
            rtn_dict[key] = dict2[key]
    return rtn_dict


def movies_merge():
    str_movie1_path = 'D:\\Program\\amms\\database\\movies_info.json'
    str_movie2_path = 'python\\movies.json'


    dict_movies_info_all = {}
    with codecs.open(str_movie1_path, 'r', 'utf-8') as f:
        dict_movies_info_all = json.load(f)

    list_movies_new = []
    with codecs.open(str_movie2_path, 'r', 'utf-8') as f:
        list_movies_new = json.load(f)

    dict_movies_new = {}
    for list1 in list_movies_new:
        if len(list1) != 2:
            print('key 2 value error')
            print(list1)
            continue
        dict_movies_new[list1[0]] = list1[1]
    
    dict_movies_info_all.update(dict_movies_new)
    movies_json = json.dumps(dict_movies_info_all, ensure_ascii=False, indent=2)
    with codecs.open('movies_all.json', 'w', 'utf-8') as f:
        f.write(movies_json)


# movies_merge()
def actors_new():
    str_actor1_path = 'D:\\Program\\amms\\database\\actors_info.json'
    str_actor2_path = 'python\\actors.json'

    dict_actors_info_all = {}
    with codecs.open(str_actor1_path, 'r', 'utf-8') as f:
        dict_actors_info_all = json.load(f)

    list_actors_info_new_all = []
    with codecs.open(str_actor2_path, 'r', 'utf-8') as f:
        list_actors_info_new_all = json.load(f)
    
    dict_actors_info_new = {}
    for list1 in list_actors_info_new_all:
        if len(list1) != 2:
            print('key 2 value error')
            print(list1)
            continue
        if list1[0] not in dict_actors_info_all.keys():
            dict_actors_info_new[list1[0]] = list1[1]
    
    actors_json_new = json.dumps(dict_actors_info_new, ensure_ascii=False, indent=2)
    with codecs.open('actors_new.json', 'w', 'utf-8') as f:
        f.write(actors_json_new)

# actors_new()


def actors_merge():
    str_actor1_path = 'D:\\Program\\amms\\database\\actors_info.json'
    str_actor2_path = 'actors_info.json'
    dict_actors_info_all = {}
    with codecs.open(str_actor1_path, 'r', 'utf-8') as f:
        dict_actors_info_all = json.load(f)

    dict_actors_new = {}
    with codecs.open(str_actor2_path, 'r', 'utf-8') as f:
        dict_actors_new = json.load(f)

    dict_actors_info_all.update(dict_actors_new)
    actors_json = json.dumps(dict_actors_info_all, ensure_ascii=False, indent=2)
    with codecs.open('actors_all.json', 'w', 'utf-8') as f:
        f.write(actors_json)

actors_merge()