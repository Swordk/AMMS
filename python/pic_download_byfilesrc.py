# -*- coding:utf-8 -*-
# Create On 20170402
# Auth: jason wong

import os
import time
import requests
import socket
import urllib
import urllib.request as request


def download_img(url, file_name):
    socket.setdefaulttimeout(15)
    url_fix = url
    pos = url_fix.find('\n')
    if pos != -1:
        url_fix = url_fix[:pos]
    print('download ' + file_name)

    opener=request.build_opener()
    opener.addheaders=[('User-Agent','Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.75 Safari/537.36')]
    request.install_opener(opener)
    try:
        request.urlretrieve(url=url_fix,filename=file_name)
    except socket.timeout:
        print('time out')
        return False
    return True

def try_to_download(url, file_name):
    b_success = False
    for tries in range(50):
        try:
            b_rtn = download_img(url, file_name)
            if b_rtn == True:
                b_success = True
                break
        except urllib.error.URLError:
            print('urllib.URLError')
            time.sleep(1)
        pass
    pass

# file_path = './'
# logfiles_all = os.listdir(file_path)
# for logfilename in sorted(logfiles_all):
#     log_file_suffix = '_pic.log'
#     if logfilename.find(log_file_suffix) != -1:
#         movie_sn = logfilename[0:len(logfilename) - len(log_file_suffix)]
#         print(movie_sn)
#         with open(logfilename, 'r') as logfile:
#             line_index = 0
#             for eachline in logfile:
#                 line_split = eachline.split(': ')
#                 # print(line_split)
#                 if len(line_split) != 2:
#                     continue
#                 if line_split[0] == 'big_pic':
#                     # while download_img(line_split[1], file_path + movie_sn + '/' + movie_sn + '.jpg') == False:
#                     try_to_download(line_split[1], file_path + movie_sn + '/' + movie_sn + '.jpg')
#                     time.sleep(1)
#                 elif line_split[0] == 'sample_pic':
#                     sample_pics_all = line_split[1].split(',')
#                     pic_index = 1
#                     for sample_pic_url in sample_pics_all:
#                         sample_pic_file = movie_sn + '_s_%02d.jpg' % pic_index
#                         pic_index += 1
#                         # while download_img(sample_pic_url, file_path + movie_sn + '/' + sample_pic_file) == False:
#                         try_to_download(sample_pic_url, file_path + movie_sn + '/' + sample_pic_file)
#                         time.sleep(1)
#                 time.sleep(3)
#         time.sleep(3)
