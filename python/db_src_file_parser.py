# -*- coding:utf-8 -*-
# Create on 20170618
# Auth: wang.yijian
# Desc: db 文件 生成器


filters_genres = [
    #
    '2014',
    # A
    'AV',
    # D
    'DMM独家', '单体作品', 'DVDトースター',
    # G
    '高画质',
    # J
    '局部特写',
    # O
    'OPEN',
    # Q
    '企画',
    # S
    '数位马赛克',
    # Y
    '亚洲女演员'
    ]


def parse_db_source_line(line_str):
    codes = line_str.split(': ')
    if len(codes) != 2:
        return False, []
    if codes[1][-1] == '\n':
        codes[1] = codes[1][:-1]
    sections = codes[1].split(' ')
    if codes[0] == 'actor':
        sections = codes[1].split(',')
    return True, codes[0], sections


def filter_generes(sections, filters):
    sections_rtn = []
    for sec in sections:
        if sec in filters:
            continue
        sections_rtn.append(sec)
    return sections_rtn


def parse_db_source_file(file_name):
    file_info_rtn = {}
    db_source_file = open(file_name, mode='r', encoding='utf-8')
    for line in db_source_file:
        line_rtn = parse_db_source_line(line)
        if line_rtn[0] == False:
            continue
        if len(line_rtn[2]) <= 0:
            continue
    
        section_rtn = line_rtn[2]
        if line_rtn[1] == 'genres':
            section_rtn = filter_generes(line_rtn[2], filters_genres)
        file_info_rtn[line_rtn[1]] = section_rtn
    return file_info_rtn
