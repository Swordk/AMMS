# -*- coding:utf-8 -*-
# Create On 20170402
# Auth: jason wong

import os
import time
from lxml import html
import requests
import re

TITLE_SUFFIX = u' - AVMOO'

def alnum_only(input_str):
    return re.sub('\D', '', input_str)

def alpha_only(input_str):
    return re.sub('[^A-Za-z]', '', input_str)


def page_search_handler(input_movie_sn):
    # @param:  input_movie_sn: Star768, Star-768, star768, STAR768
    # @return: [STAR-768, 2017-04-06, https:// ...]
    movie_s = alpha_only(input_movie_sn).upper()
    movie_n = alnum_only(input_movie_sn)
    url = 'https://avio.pw/cn/search/' + movie_s + movie_n
    
    html_page = requests.get(url)
    html_tree = html.fromstring(html_page.text)
    
    hrefs_all = html_tree.xpath(u'//a[@class="movie-box"]')
    rtn_movie_base_info = []
    for href in hrefs_all:
        movie_base_info = href.xpath(u'div[@class="photo-info"]/span/date/text()')
        if len(movie_base_info) == 2:
            sn_splited = movie_base_info[0].split('-')
            if (
                len(sn_splited) == 2
                and sn_splited[0].upper() == movie_s
                and sn_splited[1] == movie_n
            ):
                movie_base_info.append(href.get('href'))
                rtn_movie_base_info = movie_base_info
                break
    return rtn_movie_base_info


def page_detail_handler(input_movie_base_info):
    # @param:  return of page_search_handler()
    # @return: {
    #           'movie_time': '139分钟', 'series': '変態中年陵辱援交', 
    #           'genres': ['高中女生', '单体作品', '滥交', '无毛', '美少女', '凌辱', '高画质'], 
    #           'director': '五右衛門', 'producers': 'SODクリエイト', 'publisher': 'SOD star'
    #          }
    if len(input_movie_base_info) != 3:
        return
    movie_sn = input_movie_base_info[0]
    url = input_movie_base_info[2]
    
    html_page = requests.get(url)
    html_tree = html.fromstring(html_page.text)
    
    # 通过Title获取
    # STAR-768 飛鳥りん 美少女JKの変態中年陵辱援交 - AVMOO
    # movie_title = str(html_tree.xpath(u'/html/head/title/text()')[0])
    # STAR-768 飛鳥りん 美少女JKの変態中年陵辱援交
    # movie_title = movie_title[0:len(TITLE_SUFFIX)*(-1)]
    # 飛鳥りん 美少女JKの変態中年陵辱援交
    # movie_title = movie_title[len(movie_sn)+1:]

    # 通过 big image 获取
    img_big = html_tree.xpath(u'//a[@class="bigImage"]')[0]
    movie_img_big_url = img_big.get('href')
    # STAR-768 飛鳥りん 美少女JKの変態中年陵辱援交
    movie_title = img_big.get('title')
    # 飛鳥りん 美少女JKの変態中年陵辱援交
    movie_title = movie_title[len(movie_sn)+1:]
    
    rtn_detail = {}
    rtn_detail['title'] = movie_title
    rtn_detail['big_image'] = movie_img_big_url
    key_str = ''
    detail_infos_all = html_tree.xpath(u'//div[@class="col-md-3 info"]/p')
    for detail_info in detail_infos_all:
        child_class = detail_info.get('class')
        if child_class == None:
            if key_str == u'制作商: ':
                rtn_detail[u'producers'] = str(detail_info.xpath(u'a/text()')[0])
            elif key_str == u'发行商: ':
                rtn_detail[u'publisher'] = str(detail_info.xpath(u'a/text()')[0])
            elif key_str == u'系列:':
                rtn_detail[u'series'] = str(detail_info.xpath(u'a/text()')[0])
            elif key_str == u'类别:':
                genres_all = detail_info.xpath(u'span/a/text()')
                if len(genres_all) > 0:
                    rtn_detail[u'genres'] = []
                    for genre in genres_all:
                        rtn_detail[u'genres'].append(str(genre))
            else:
                child_text = detail_info.xpath(u'span/text()')
                if len(child_text) == 2:
                    if child_text[0] == u'识别码:':
                        continue
                        rtn_detail[u'sn'] = child_text[1]
                    else:
                        print('new 2 field')
                elif len(child_text) == 1:
                    if child_text[0] == u'发行时间:':
                        continue
                        key_str = u'date'
                    elif child_text[0] == u'长度:':
                        key_str = u'movie_time'
                    elif child_text[0] == u'导演:':
                        rtn_detail[u'director'] = str(detail_info.xpath(u'a/text()')[0])
                        continue
                    rtn_detail[key_str] = str(detail_info.xpath(u'text()')[0])
            key_str = ''
        else:
            key_str = detail_info.text
            pass
    # 删除不必要的空格
    if u'movie_time' in rtn_detail.keys():
        rtn_detail[u'movie_time'] = re.sub(' ', '', rtn_detail[u'movie_time'])

    actors_info_all = html_tree.xpath(u'//a[@class="avatar-box"]')
    if len(actors_info_all) > 0:
        # name:url
        rtn_detail['actors_info'] = {}
        for actor_info in actors_info_all:
            actor_url = actor_info.get('href')
            actor_name = actor_info.xpath(u'span/text()')[0]
            rtn_detail['actors_info'][actor_name] = [actor_url]

    sample_pics_all = html_tree.xpath(u'//a[@class="sample-box"]')
    if len(sample_pics_all) > 0:
        rtn_detail['sample_pic'] = []
        for sample_pic in sample_pics_all:
            rtn_detail['sample_pic'].append(str(sample_pic.get('href')))
    
    return rtn_detail

# movie_base_info = page_search_handler("Star768")
# movie_base_info = ['STAR-768', '2017-04-06', 'https://avmo.pw/cn/movie/5zhz']
# movie_base_info = ['TPPN-152', '2017-04-06', 'https://avmo.pw/cn/movie/5zcz']
# print(movie_base_info)

# movie_detail_info = page_detail_handler(movie_base_info)
# print(movie_detail_info)



file_path = './'
print(file_path)

actors_dict = {}

folders_all = os.listdir(file_path)
for folder in sorted(folders_all):
    if folder.find('.py') != -1 or folder.find('.log') != -1 or folder.find('.db') != -1:
        continue
    print(folder)
    movie_base_info = page_search_handler(folder)
    if len(movie_base_info) <= 0:
        continue
    movie_detail_info = page_detail_handler(movie_base_info)
    if len(movie_detail_info) <= 0:
        continue
    print(movie_base_info, movie_detail_info)
    with open(folder+'.db', 'w') as file_db:
        file_db.write('sn: ' + movie_base_info[0] + '\n')
        file_db.write('date: ' + movie_base_info[1] + '\n')
        for key in movie_detail_info.keys():
            if key == 'genres':
                genres_str = ''
                for genres in movie_detail_info[key]:
                    genres_str += genres + ' '
                
                if len(genres_str) > 1:
                    genres_str = genres_str[:-1]
                    file_db.write('genres: ' + genres_str + '\n')
            elif key == 'actors_info':
                actor_str = ''
                for actor in movie_detail_info[key].keys():
                    actor_str += actor + ','
                    if actor not in actors_dict.keys():
                        actors_dict[actor] = movie_detail_info[key][actor]
                if len(actor_str) > 1:
                    actor_str = actor_str[:-1]
                    file_db.write('actor: ' + actor_str + '\n')
            elif key == 'sample_pic':
                sample_pic_str = ''
                for sample_pic in movie_detail_info[key]:
                    sample_pic_str += sample_pic + ','
                if len(sample_pic_str) > 1:
                    sample_pic_str = sample_pic_str[:-1]
                    with open(folder+'_pic.log', 'a') as file_pic:
                        file_pic.write('sample_pic: ' + sample_pic_str + '\n')
            elif key == 'big_image':
                with open(folder+'_pic.log', 'a') as file_pic:
                    file_pic.write('big_pic: ' + movie_detail_info[key] + '\n')

            else:
                file_db.write(key + ': ' + movie_detail_info[key] + '\n')

    time.sleep(3)

with open('actors.db', 'a') as actors_db:
    for key in actors_dict.keys():
        actors_db.write(key + ': ' + actors_dict[key] + '\n')
