#ifndef CHATMAPPEREXPORT_H
#define CHATMAPPEREXPORT_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPalette>
#include <QFileDialog>
#include <QFile>
#include <QMap>

#include <MainWindow.h>
#include "Data/Json.h"
#include "Data/Validation.h"
#include "CustomWidgets/ResultDialog.h"
#include "CustomWidgets/CustomField.h"

namespace Ui {
class ChatmapperExport;
}

class ChatmapperExport : public QWidget
{
    Q_OBJECT

public:
    explicit ChatmapperExport(QWidget *parent = nullptr);
    ~ChatmapperExport();

    //Custom fields
    CustomField *silence;
    CustomField *multi;
    CustomField *change;
    CustomField *int01Cont;
    CustomField *int02Nexus;
    CustomField *int03Node;
    CustomField *intNpc;    

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void browserFile();
    void exportJsonFile();
    void selectGame(const int index);

private:
    Ui::ChatmapperExport *ui;

    MainWindow *parent_;
    Json *jsonFile_;
    QMap<int, QString> *gamesMap;

    void addCustomFields();
    void addGames();

};

#endif // CHATMAPPEREXPORT_H
