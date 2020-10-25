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

//    QMainWindow::showMaximized();

    const int mainWindowPercentWidtch = 30;
    int mainWindowWidth = getWindowWidth() * mainWindowPercentWidtch / 100;
    const int mainWindowPercentHeight = 70;
    int mainWindowHeight = getWindowHeight() * mainWindowPercentHeight / 100;
    int mainWindowX = (getWindowWidth() / 2) - (mainWindowWidth / 2);
    int mainWindowY = (getWindowHeight() / 2) - (mainWindowHeight / 2);
    this->setGeometry(mainWindowX,
                      mainWindowY,
                      mainWindowWidth,
                      mainWindowHeight);
    this->setMinimumSize(mainWindowWidth, mainWindowHeight);

    widgetChatmapper = new ChatmapperExport(this);
    ui->horizontalLayout->addWidget(widgetChatmapper);
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

