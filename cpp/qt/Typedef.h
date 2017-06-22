/////////////////////////////////////////////////////////////////////////﻿
///常用的类型定义
///20170622 jason wong 创建该文件
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

typedef boost::shared_lock<boost::shared_mutex> readLock;
typedef boost::unique_lock<boost::shared_mutex> writeLock;

#ifndef _DOUBLE_ZERO_VALUE_
#define _DOUBLE_ZERO_VALUE_     0.000000000000001
#endif
