# -*- coding:utf-8 -*-
# Create on 20170620
# Auth: wang.yijian
# Desc: mo page 处理器

import requests
import re
import time
from lxml import html
import string_handler as str_handler

# ##################################################################################################
def page_search_handler(input_movie_sn, web_url = 'avio.pw'):
    '''
    @introducation: 查找页面处理，找出sn对应的微缩图和网页链接
    @param:
        web_url:        avio.pw
        input_movie_sn: Star768, Star-768, star768, STAR768, STAR-768
    @return:
        dict:   ['sn']
                ['url']
                ['preview_pic']
    '''
    movie_s = str_handler.alpha_only(input_movie_sn).upper()
    movie_n = str_handler.alnum_only(input_movie_sn)
    url = 'https://' + web_url + '/cn/search/' + movie_s + movie_n

    html_page = None
    while True:
        html_page = requests.get(url)
        if html_page.ok == True:
            break
        else:
            print('requests.get failed, retry ...')
            time.sleep(1)


    html_tree = html.fromstring(html_page.text)

    hrefs_all = html_tree.xpath(u'//a[@class="movie-box"]')
    rtn_movie_base_info = {}
    for href in hrefs_all:
        movie_base_info = href.xpath(u'div[@class="photo-info"]/span/date/text()')
        if len(movie_base_info) != 2:
            continue
        sn_splited = movie_base_info[0].split('-')
        if len(sn_splited) != 2 or sn_splited[0].upper() != movie_s or sn_splited[1] != movie_n:
            continue

        rtn_movie_base_info['sn'] = movie_base_info[0]
        rtn_movie_base_info['url'] = href.get('href')

        photo_frame = href.xpath(u'div[@class="photo-frame"]/img')
        if len(photo_frame) <= 0:
            break
        rtn_movie_base_info['preview_pic'] = photo_frame[0].get('src')
        break

    return rtn_movie_base_info

# rtn = page_search_handler('ABS-221')
# print(rtn)
# return: {
#   'sn': 'ABS-221',
#   'url': 'https://avio.pw/cn/movie/1noy',
#   'preview_pic': 'https://jp.netcdn.space/digital/video/118abs00221/118abs00221ps.jpg'
# }


def page_detail_handler(movie_sn, url):
    '''
    @introducation: 处理详情页面
    '''
    html_page = None
    while True:
        html_page = requests.get(url)
        if html_page.ok == True:
            break
        else:
            print('requests.get failed, retry ...')
            time.sleep(1)

    html_tree = html.fromstring(html_page.text)
    
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
                        rtn_detail[u'sn'] = child_text[1]
                        continue
                    else:
                        print('new 2 field')
                elif len(child_text) == 1:
                    if child_text[0] == u'发行时间:':
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
    actors_info = {}
    if len(actors_info_all) > 0:
        # name:url
        rtn_detail['actors'] = []
        for actor_info in actors_info_all:
            actor_url = actor_info.get('href')
            actor_name = actor_info.xpath(u'span/text()')[0]
            rtn_detail['actors'].append(actor_name)
            actors_info[actor_name] = actor_url

    sample_pics_all = html_tree.xpath(u'//a[@class="sample-box"]')
    if len(sample_pics_all) > 0:
        rtn_detail['sample_pic'] = []
        for sample_pic in sample_pics_all:
            rtn_detail['sample_pic'].append(str(sample_pic.get('href')))
    
    return rtn_detail, actors_info

# rtn = page_detail_handler('ABS-221', 'https://avio.pw/cn/movie/1noy')
# print(rtn)
# return: (
#   {
#       'big_image': 'https://jp.netcdn.space/digital/video/118abs00221/118abs00221pl.jpg',
#       'genres': ['多P', '单体作品', '潮吹'],
#       'publisher': 'ABSOLUTE',
#       'series': '天然成分由来○○汁100％',
#       'sample_pic': [
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-1.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-2.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-3.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-4.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-5.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-6.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-7.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-8.jpg',
#           'https://jp.netcdn.space/digital/video/118abs00221/118abs00221jp-9.jpg'
#       ],
#       'producers': 'プレステージ',
#       'movie_time': '118分钟',
#       'actors': ['あやみ旬果'],
#       'title': '天然成分由来あやみ旬果汁100％ あやみ旬果の体液'
#   },
#   {
#       'あやみ旬果': 'https://avio.pw/cn/star/2yl'
#   }
# )



def page_actor_handler(url):
    '''
    处理演员页面
    '''
    html_page = None
    while True:
        html_page = requests.get(url)
        if html_page.ok == True:
            break
        else:
            print('requests.get failed, retry ...')
            time.sleep(1)
    
    html_tree = html.fromstring(html_page.text)
    avatar_box = html_tree.xpath(u'//div[@class="avatar-box"]')
    actor_img = avatar_box[0].xpath(u'div[@class="photo-frame"]/img')
    actor_img_url = actor_img[0].get('src')

    dict_actor_info = {}
    actor_info_details = avatar_box[0].xpath(u'div[@class="photo-info"]/p/text()')
    for actor_info in actor_info_details:
        splits = actor_info.split(': ')
        if len(splits) != 2:
            continue
        if splits[0] == '生日':
            dict_actor_info['birth_day'] = splits[1]
        elif splits[0] == '身高':
            dict_actor_info['height'] = splits[1]
        elif splits[0] == '罩杯':
            dict_actor_info['cup'] = splits[1]
        elif splits[0] == '胸围':
            dict_actor_info['bust'] = splits[1]
        elif splits[0] == '腰围':
            dict_actor_info['waist'] = splits[1]
        elif splits[0] == '臀围':
            dict_actor_info['hip'] = splits[1]
        elif splits[0] == '爱好':
            dict_actor_info['hobby'] = splits[1].split(u'、')
    return actor_img_url, dict_actor_info

# julia
# print(page_actor_handler('https://avio.pw/cn/star/2de'))
# return: (
#   'https://jp.netcdn.space/mono/actjpgs/julia.jpg',
#   {
#       'birth_day': '1987-05-25',
#       'height': '158cm',
#       'cup': 'J',
#       'bust': '102cm',
#       'waist': '55cm',
#       'hip': '84cm',
#       'hobby': ['自分磨き', '簿記二級']
#   }
# )
