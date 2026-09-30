#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "compacttreeview.h"
#include "flowcontainer.h"
#include "vflowlayout.h"

#include <QEvent>
#include <QIcon>
#include <QScrollArea>
#include <QStandardItemModel>
#include <QStyle>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , ui{new Ui::MainWindow}
{
    ui->setupUi(this);

    delete ui->scrollArea->takeWidget();
    auto *container = new FlowContainer;
    ui->scrollArea->setWidget(container);
    ui->scrollArea->viewport()->installEventFilter(this);

    const QIcon folderIcon = style()->standardIcon(QStyle::SP_DirIcon);
    const QIcon itemIcon = style()->standardIcon(QStyle::SP_FileIcon);

    for (int treeIndex = 0; treeIndex < 8; ++treeIndex) {
        auto *treeView = new CompactTreeView{container};
        auto *model = new QStandardItemModel{treeView};

        auto *parentItem = new QStandardItem{folderIcon, QStringLiteral("Раздел %1").arg(treeIndex + 1)};
        for (int childIndex = 0; childIndex < 5; ++childIndex) {
            parentItem->appendRow(new QStandardItem{
                itemIcon,
                QStringLiteral("Элемент %1").arg(childIndex + 1)});
        }

        model->appendRow(parentItem);
        treeView->setModel(model);
        treeView->setExpanded(parentItem->index(), true);
        container->flowLayout()->addWidget(treeView);
    }

    QTimer::singleShot(0, this, &MainWindow::updateFlowGeometry);
}

MainWindow::~MainWindow() = default;

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->scrollArea->viewport() && event->type() == QEvent::Resize)
        updateFlowGeometry();

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::updateFlowGeometry()
{
    auto *container = static_cast<FlowContainer *>(ui->scrollArea->widget());
    container->setViewportSize(ui->scrollArea->viewport()->size());
}