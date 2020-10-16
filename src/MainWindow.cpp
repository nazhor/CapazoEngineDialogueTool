#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <CustomWidgets/ChatmapperExport.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Capazo Engine Dialogue Tool");
    setWindowIcon(QIcon(":/images/tbdh.png"));

    QMainWindow::showMaximized();

    widgetChatmapper = new ChatmapperExport(this);
    //widget_chme = new ChatmapperExport();
    widgetChatmapper->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getWindowWidth()
{
    return QGuiApplication::primaryScreen()->availableGeometry().width();
}

int MainWindow::getWindowHeight()
{
    return QGuiApplication::primaryScreen()->availableGeometry().height();
}

