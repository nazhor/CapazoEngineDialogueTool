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

    static int GetWindowWidth();
    static int GetWindowHeight();

private:
    Ui::MainWindow *ui;

    ChatmapperExport *widget_chme;
};
#endif // MAINWINDOW_H
