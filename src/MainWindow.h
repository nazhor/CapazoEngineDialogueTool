#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QRect>

class ChatmapperExport;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static int getWindowWidth();
    static int getWindowHeight();

private:
    Ui::MainWindow *ui;

    ChatmapperExport *widgetChatmapper;
};
#endif // MAINWINDOW_H
