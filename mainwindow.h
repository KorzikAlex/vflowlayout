#pragma once

#include <memory>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow
    : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void updateFlowGeometry();

    std::unique_ptr<Ui::MainWindow> ui;
};
