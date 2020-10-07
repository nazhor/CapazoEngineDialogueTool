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

    //widget_chme = new ChatmapperExport(this);
    widget_chme = new ChatmapperExport();
    widget_chme->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::GetWindowWidth()
{
    return QGuiApplication::primaryScreen()->availableGeometry().width();
}

int MainWindow::GetWindowHeight()
{
    return QGuiApplication::primaryScreen()->availableGeometry().height();
}

