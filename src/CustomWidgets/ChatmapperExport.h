#ifndef CHATMAPPEREXPORT_H
#define CHATMAPPEREXPORT_H

#include <QWidget>
#include <QDebug>

#include <MainWindow.h>

namespace Ui {
class ChatmapperExport;
}

class ChatmapperExport : public QWidget
{
    Q_OBJECT

public:
    explicit ChatmapperExport(QWidget *parent = nullptr);
    ~ChatmapperExport();

private:
    Ui::ChatmapperExport *ui;

    MainWindow *Parent;
};

#endif // CHATMAPPEREXPORT_H
