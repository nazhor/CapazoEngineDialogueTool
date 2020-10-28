#ifndef CUSTOMFIELD_H
#define CUSTOMFIELD_H

#include <QWidget>
#include <QPainter>
#include <QString>

namespace Ui {
class CustomField;
}

class CustomField : public QWidget
{
    Q_OBJECT

public:
    explicit CustomField(const QString& name, QWidget *parent = nullptr);
    ~CustomField();

    bool getCheckStatus() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::CustomField *ui;


};

#endif // CUSTOMFIELD_H
