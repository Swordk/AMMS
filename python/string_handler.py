# -*- coding:utf-8 -*-
# Create on 20170620
# Auth: wang.yijian
# Desc: 字符串处理

import re

def alnum_only(input_str):
    return re.sub('\D', '', input_str)

def alpha_only(input_str):
    return re.sub('[^A-Za-z]', '', input_str)