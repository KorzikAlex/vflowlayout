#pragma once

#include <QWidget>

class VFlowLayout;

class FlowContainer : public QWidget
{
public:
    explicit FlowContainer(QWidget *parent = nullptr);

    VFlowLayout *flowLayout() const;
    void setViewportSize(const QSize &size);

private:
    VFlowLayout *layout = nullptr;
};