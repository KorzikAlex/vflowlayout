#include "vflowlayout.h"

#include <QWidget>

#include <algorithm>
#include <limits>

VFlowLayout::VFlowLayout(QWidget *parent, int margin, int spacing)
    : QLayout{parent}
{
    setContentsMargins(margin, margin, margin, margin);
    setSpacing(spacing);
}

VFlowLayout::~VFlowLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)) != nullptr)
        delete item;
}

void VFlowLayout::addItem(QLayoutItem *item)
{
    items.append(item);
}

int VFlowLayout::count() const
{
    return items.size();
}

QLayoutItem *VFlowLayout::itemAt(int index) const
{
    return index >= 0 && index < items.size() ? items.at(index) : nullptr;
}

QLayoutItem *VFlowLayout::takeAt(int index)
{
    return index >= 0 && index < items.size() ? items.takeAt(index) : nullptr;
}

QSize VFlowLayout::sizeHint() const
{
    return minimumSize();
}

QSize VFlowLayout::minimumSize() const
{
    QSize result;
    for (const QLayoutItem *item : items)
        result = result.expandedTo(item->minimumSize());

    const QMargins margins = contentsMargins();
    return result + QSize(margins.left() + margins.right(), margins.top() + margins.bottom());
}

void VFlowLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize VFlowLayout::sizeForHeight(int height) const
{
    const QMargins margins = contentsMargins();
    const int innerHeight = std::max(0, height - margins.top() - margins.bottom());
    const int width = doLayout(QRect{0, 0, std::numeric_limits<int>::max(), innerHeight}, true);
    return {width + margins.left() + margins.right(), height};
}

int VFlowLayout::doLayout(const QRect &rect, bool testOnly) const
{
    const QMargins margins = contentsMargins();
    const QRect effectiveRect = rect.adjusted(margins.left(), margins.top(),
                                              -margins.right(), -margins.bottom());
    const int spacing = this->spacing();
    const int columnHeight = effectiveRect.height();
    int x = effectiveRect.x();
    int y = effectiveRect.y();
    int columnWidth = 0;

    for (QLayoutItem *item : items) {
        const QSize itemSize = item->sizeHint();
        if (y != effectiveRect.y() && y + itemSize.height() > effectiveRect.bottom() + 1) {
            x += columnWidth + spacing;
            y = effectiveRect.y();
            columnWidth = 0;
        }

        if (!testOnly)
            item->setGeometry(QRect{x, y, itemSize.width(), itemSize.height()});

        y += itemSize.height() + spacing;
        columnWidth = std::max(columnWidth, itemSize.width());
    }

    Q_UNUSED(columnHeight)
    return x + columnWidth - effectiveRect.x();
}