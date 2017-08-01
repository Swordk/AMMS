# -*- coding:utf-8 -*-
# Create on 20170801
# Auth: wang.yijian
# Desc: 电影目录处理


import os
import shutil

def movie_dir_regroup(movie_path):
    '''
    DIR: Series/Series-No
    '''
    folders_all = os.listdir(movie_path)
    for folder in folders_all:
        dir_full = movie_path + '/' + folder
        if os.path.isdir(dir_full) == False:
            print(dir_full + ' is not a dir')
            continue
        sns = folder.split('-')
        if len(sns) != 2:
            print(folder + ' is not a series no')
            continue
        series = sns[0]
        series_dir = movie_path + '/' + series
        no = sns[1]
        if os.path.exists(series_dir) == False:
            os.mkdir(series_dir)
        shutil.move(dir_full, series_dir)


# movie_dir_regroup('F:\\SublimeText3\\Data\\d\\2\\1')