#include "ChatmapperExport.h"
#include "ui_ChatmapperExport.h"

ChatmapperExport::ChatmapperExport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatmapperExport)
{
    ui->setupUi(this);

    const int MenuScreenPercent = 30;
    int WidgetWidth = MainWindow::GetWindowWidth() * MenuScreenPercent / 100;
    int WidgetHeight = MainWindow::GetWindowHeight() * MenuScreenPercent / 100;
    int WidgetX = (MainWindow::GetWindowWidth() / 2) - (WidgetWidth / 2);
    int WidgetY = (MainWindow::GetWindowHeight() / 2) - (WidgetHeight / 2);
    this->setGeometry(WidgetX,
                      WidgetY,
                      WidgetWidth,
                      WidgetHeight
                );
    qInfo() << WidgetWidth << "_" << WidgetHeight << "_" << WidgetX << "_" << WidgetY << "_" << MainWindow::GetWindowWidth() << "_" << MainWindow::GetWindowHeight();
}

ChatmapperExport::~ChatmapperExport()
{
    delete ui;
}
