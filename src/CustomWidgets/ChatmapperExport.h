#ifndef CHATMAPPEREXPORT_H
#define CHATMAPPEREXPORT_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPalette>
#include <QFileDialog>
#include <MainWindow.h>

#include "Data/Json.h"

namespace Ui {
class ChatmapperExport;
}

class ChatmapperExport : public QWidget
{
    Q_OBJECT

public:
    explicit ChatmapperExport(QWidget *parent = nullptr);
    ~ChatmapperExport();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void browserFile();
    void exportJsonFile();

private:
    Ui::ChatmapperExport *ui;

    MainWindow *parent_;

};

#endif // CHATMAPPEREXPORT_H
