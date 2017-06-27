# -*- coding:utf-8 -*-
# Create on 20170618
# Auth: wang.yijian
# Desc: 下载电影图片

import os
import sys
import json
import codecs
import pic_downloader as picd


if __name__ == '__main__':
    movie_path = './'
    if len(sys.argv) > 2:
        print('Usage:')
        print('    ' + sys.argv[0] + ' movie_path')
        exit(1)
    if len(sys.argv) == 2:
        movie_path = sys.argv[1] + '/'
    
    # movie_path = 'X:\\SublimeText3\\Data\\d\\2\\00.done\\0'
    print(movie_path)

    dict_movies_pics_all = {}
    with codecs.open('pics.json', 'r', 'utf-8') as f:
        dict_movies_pics_all = json.load(f)
    
    keys = sorted(dict_movies_pics_all.keys())
    for movie_sn in keys:
        s_dir = movie_sn.split('-')[0]
        target_dir = movie_path + '/' + s_dir + '/' + movie_sn
        if 'preview_pic' in dict_movies_pics_all[movie_sn].keys():
            url = dict_movies_pics_all[movie_sn]['preview_pic']
            file_name = target_dir + '/' + movie_sn + '_ps.jpg'
            picd.try_to_download(url, file_name)
        if 'big_image' in dict_movies_pics_all[movie_sn].keys():
            url = dict_movies_pics_all[movie_sn]['big_image']
            file_name = target_dir + '/' + movie_sn + '.jpg'
            picd.try_to_download(url, file_name)
        if 'sample_pic' in dict_movies_pics_all[movie_sn].keys():
            pic_index=1
            for url in dict_movies_pics_all[movie_sn]['sample_pic']:
                file_name = target_dir + '/' + movie_sn + '_s_%02d.jpg' % pic_index
                picd.try_to_download(url, file_name)
                pic_index += 1
    print('done')
    