/////////////////////////////////////////////////////////////////////////﻿
///DynamicGridWidget
///20160919 jason wong 创建该文件
///随着窗口大小变化，可动态调整每行Widget数量的GridWidget
/////////////////////////////////////////////////////////////////////////

#include "MovieWallWidget.h"

namespace amms {
    void CMovieWallWidget::Init(QSize frameSize)
    {
        this->setViewMode(QListView::IconMode);
        this->setIconSize(frameSize);
        this->setResizeMode(QListView::ResizeMode::Adjust);
        this->setMovement(QListView::Movement::Static);
        this->setSpacing(5);
    }

}
