#include "flowcontainer.h"

#include "vflowlayout.h"

#include <algorithm>

FlowContainer::FlowContainer(QWidget *parent)
    : QWidget{parent}
    , layout{new VFlowLayout{this, 8, 8}}
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

VFlowLayout *FlowContainer::flowLayout() const
{
    return layout;
}

void FlowContainer::setViewportSize(const QSize &size)
{
    const int height = std::max(1, size.height());
    const int width = std::max(size.width(), layout->sizeForHeight(height).width());
    setFixedSize(width, height);
}