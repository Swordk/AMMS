# -*- coding:utf-8 -*-
# Create on 20170620
# Auth: wang.yijian
# Desc: 下载图片

import socket
import requests
import socket
import urllib
import urllib.request as request
import time
import traceback

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
        except :
            traceback.print_exc()
            time.sleep(1)
        pass
    pass