#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QPalette>
#include <QPixmap>
#include <QMovie>

#include "MainWindow.h"

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(const bool result, QWidget *parent = nullptr);
    ~ResultDialog();

protected:
    void paintEvent(QPaintEvent *event);

private slots:
    void handle_btn_ok();

private:
    Ui::ResultDialog *ui;

};

#endif // RESULTDIALOG_H
