#pragma once

#include <QLayout>

class VFlowLayout : public QLayout
{
public:
    explicit VFlowLayout(QWidget *parent = nullptr, int margin = -1, int spacing = -1);
    ~VFlowLayout() override;

    void addItem(QLayoutItem *item) override;
    int count() const override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &rect) override;

    QSize sizeForHeight(int height) const;

private:
    int doLayout(const QRect &rect, bool testOnly) const;

    QList<QLayoutItem *> items;
};