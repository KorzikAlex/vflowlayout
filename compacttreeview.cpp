#include "compacttreeview.h"

#include <QAbstractItemModel>

#include <algorithm>

CompactTreeView::CompactTreeView(QWidget *parent)
    : QTreeView{parent}
{
    setHeaderHidden(true);
    setRootIsDecorated(true);
    setUniformRowHeights(true);
    setIndentation(18);
    setIconSize({16, 16});
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setFixedWidth(220);

    connect(this, &QTreeView::expanded, this, &CompactTreeView::updateHeight);
    connect(this, &QTreeView::collapsed, this, &CompactTreeView::updateHeight);
}

void CompactTreeView::setModel(QAbstractItemModel *newModel)
{
    QTreeView::setModel(newModel);
    connect(newModel, &QAbstractItemModel::modelReset, this, &CompactTreeView::updateHeight);
    connect(newModel, &QAbstractItemModel::rowsInserted, this, &CompactTreeView::updateHeight);
    connect(newModel, &QAbstractItemModel::rowsRemoved, this, &CompactTreeView::updateHeight);
    updateHeight();
}

void CompactTreeView::updateHeight()
{
    if (!model())
        return;

    const QModelIndex root;
    int visibleRows = model()->rowCount(root);
    for (int row = 0; row < model()->rowCount(root); ++row) {
        const QModelIndex parentIndex = model()->index(row, 0, root);
        if (isExpanded(parentIndex))
            visibleRows += model()->rowCount(parentIndex);
    }

    const int rowHeight = std::max(24, fontMetrics().height() + 8);
    const int frame = 2 * frameWidth();
    setFixedHeight(frame + visibleRows * rowHeight);
}