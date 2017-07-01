# -*- coding:utf-8 -*-
# Create on 20170618
# Auth: wang.yijian
# Desc: db src actor 文件生成

import os
import sys
import json
import codecs
import mo_page_handler as mph
import pic_downloader as picd

def process(movie_path):
    pass


if __name__ == '__main__':
    actor_pic_path = 'actor_pic'
    if len(sys.argv) > 2:
        print('Usage:')
        print('    ' + sys.argv[0] + ' actor_pic_path')
        exit(1)
    if len(sys.argv) == 2:
        actor_pic_path = sys.argv[1] + '/'
    
    actors = ''
    with codecs.open('actors.json', 'r', 'utf-8') as f:
        actors = json.load(f)
    
    dict_actors_info_all = {}
    for actor_name in actors:
        print(actor_name)
        actor_url = actors[actor_name]
        actor_pic_url, actor_info = mph.page_actor_handler(actor_url)
        dict_actors_info_all[actor_name] = actor_info

        # pic_file_name = actor_pic_path + '/' + actor_name + '.jpg'
        # picd.try_to_download(actor_pic_url, pic_file_name)
    

    actors_json = json.dumps(dict_actors_info_all, ensure_ascii=False, indent=2)
    with codecs.open('actors_info.json', 'w', 'utf-8') as f:
        f.write(actors_json)
    
    print('done')
    