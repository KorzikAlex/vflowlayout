#pragma once

#include <QTreeView>

class CompactTreeView : public QTreeView
{
public:
    explicit CompactTreeView(QWidget *parent = nullptr);

    void setModel(QAbstractItemModel *model) override;

private:
    void updateHeight();
};