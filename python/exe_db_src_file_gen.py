# -*- coding:utf-8 -*-
# Create on 20170618
# Auth: wang.yijian
# Desc: db src 文件 生成器

import os
import sys
import time
import json
import codecs
import mo_page_handler as mph

if __name__ == '__main__':
    movie_path = './'
    if len(sys.argv) > 2:
        print('Usage:')
        print('    ' + sys.argv[0] + ' movie_path')
        exit(1)
    if len(sys.argv) == 2:
        movie_path = sys.argv[1] + '/'
    
    dict_movies_info = {}
    dict_movies_pics = {}
    dict_actors_info = {}
    folders_all = os.listdir(movie_path)
    for folder in sorted(folders_all):
        # 每次开始之前sleep 3秒，避免被封
        time.sleep(3)

        if folder.find('.py') != -1 or folder.find('.log') != -1 or folder.find('.db') != -1 or folder.find('.json') != -1:
            continue
        
        print('processing search page: ' + folder)
        # process search page
        rtn_movie_base_info = mph.page_search_handler(folder)
        preview_pic = ''
        if 'preview_pic' in rtn_movie_base_info.keys():
            preview_pic = rtn_movie_base_info['preview_pic']
        if 'sn' not in rtn_movie_base_info.keys() or 'url' not in rtn_movie_base_info.keys():
            print('     Failed ...')
            continue
        sn = rtn_movie_base_info['sn']
        url = rtn_movie_base_info['url']
        if sn == '' or url == '':
            print('     Failed ...')
            continue
        
        # process detail page
        time.sleep(1)
        print('processing detail page: ' + sn)
        movies_pics = {}
        rtn_detail, actors_info = mph.page_detail_handler(sn, url)
        # pics
        if preview_pic != '':
            movies_pics['preview_pic'] = preview_pic
        if 'sample_pic' in rtn_detail.keys():
            movies_pics['sample_pic'] = rtn_detail['sample_pic']
            del rtn_detail['sample_pic']
        if 'big_image' in rtn_detail.keys():
            movies_pics['big_image'] = rtn_detail['big_image']
            del rtn_detail['big_image']
        dict_movies_pics[sn] = movies_pics

        rtn_detail['url'] = url
        dict_movies_info[sn] = rtn_detail
        # actors
        if len(actors_info) > 0:
            dict_actors_info.update(actors_info)
        print(u'√')
    
    # 生成文件
    movies_json = json.dumps(dict_movies_info, ensure_ascii=False, indent=2)
    with codecs.open('movies.json', 'w', 'utf-8') as f:
        f.write(movies_json)
    
    actors_json = json.dumps(dict_actors_info, ensure_ascii=False, indent=2)
    with codecs.open('actors.json', 'w', 'utf-8') as f:
        f.write(actors_json)

    pics_json = json.dumps(dict_movies_pics, ensure_ascii=False, indent=2)
    with codecs.open('pics.json', 'w', 'utf-8') as f:
        f.write(pics_json)