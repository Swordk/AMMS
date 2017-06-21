# -*- coding:utf-8 -*-
# Create on 20170620
# Auth: wang.yijian
# Desc: mo page 处理器

import requests
import re
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

    html_page = requests.get(url)
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

# rtn = page_search_handler('ABP-135')
# print(rtn)
# return: {'sn': 'ABP-135', 'preview_pic': 'https://jp.netcdn.space/digital/video/118abp00135/118abp00135ps.jpg', 'url': 'https://avio.pw/cn/movie/486t'}


def page_detail_handler(movie_sn, url):
    '''
    @introducation: 处理详情页面
    '''
    html_page = requests.get(url)
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

# rtn = page_detail_handler('ABP-135', 'https://avio.pw/cn/movie/486t')
# print(rtn)
# return: ({'big_image': 'https://jp.netcdn.space/digital/video/118abp00135/118abp00135pl.jpg', 'producers': 'プレステージ', 'director': 'マンハッタン木村', 'series': '天然成分由来○○汁100％', 'actors': ['芽森しずく'], 'genres': ['多P', '巨乳', '单体作品', '高画质'], 'title': '天然成分由来 芽森しずく汁120%', 'publisher': 'ABSOLUTELY PERFECT', 'movie_time': '130分钟'}, {'芽森しずく': 'https://avio.pw/cn/star/mft'})

