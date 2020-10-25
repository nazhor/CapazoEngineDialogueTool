#include "ResultDialog.h"
#include "ui_ResultDialog.h"

ResultDialog::ResultDialog(const bool result, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);

    this->setAutoFillBackground(true);
    QPalette palb = palette();
    QPixmap pattern(":/images/pattern.png");
    palb.setBrush(QPalette::Background, pattern);
    this->setPalette(palb);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    QMovie *gif;
    if (result)
    {
        gif = new QMovie(":/images/ok.gif");
    }
    else
    {
        gif = new QMovie(":/images/error.gif");
    }
    ui->label_image->setMovie(gif);
    gif->start();

    connect(ui->pushButton_ok, SIGNAL(released()), this, SLOT(handle_btn_ok()));
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::white, 5);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
}

void ResultDialog::handle_btn_ok()
{
    accept();
}
