#include "CustomField.h"
#include "ui_CustomField.h"

CustomField::CustomField(const QString& name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomField)
{
    ui->setupUi(this);

    ui->checkBox_custom_field->setText(name);

    this->setAutoFillBackground(true);
    QPalette palb = palette();
    palb.setBrush(QPalette::Background, Qt::transparent);
    this->setPalette(palb);
}

CustomField::~CustomField()
{
    delete ui;
}

void CustomField::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::white, 2);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
}

bool CustomField::getCheckStatus() const
{
    return ui->checkBox_custom_field->isChecked();
}

void CustomField::setCheckStatus(const bool state)
{
    ui->checkBox_custom_field->setChecked(state);
}

