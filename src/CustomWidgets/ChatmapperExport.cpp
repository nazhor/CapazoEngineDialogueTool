#include "ChatmapperExport.h"
#include "ui_ChatmapperExport.h"

ChatmapperExport::ChatmapperExport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatmapperExport)
{
    ui->setupUi(this);

    const int menuScreenPercentWidtch = 30;
    int widgetWidth = MainWindow::getWindowWidth() * menuScreenPercentWidtch / 100;
    const int menuScreenPercentHeight = 70;
    int widgetHeight = MainWindow::getWindowHeight() * menuScreenPercentHeight / 100;
    int widgetX = (MainWindow::getWindowWidth() / 2) - (widgetWidth / 2);
    int widgetY = (MainWindow::getWindowHeight() / 2) - (widgetHeight / 2);
    this->setGeometry(widgetX,
                      widgetY,
                      widgetWidth,
                      widgetHeight);

    this->setAutoFillBackground(true);
    QPalette palb = palette();
    QPixmap pattern(":/images/pattern.png");
    palb.setBrush(QPalette::Background, pattern);
    this->setPalette(palb);
    QPalette palf = palette();
    palf.setBrush(QPalette::WindowText, Qt::white);
    ui->groupBox_actors->setPalette(palf);
    ui->groupBox_custom_fields->setPalette(palf);

    connect(ui->pushButton_browser_file, SIGNAL(released()), this, SLOT(browserFile()));
    connect(ui->pushButton_export_json, SIGNAL(released()), this, SLOT(exportJsonFile()));
}

ChatmapperExport::~ChatmapperExport()
{
    delete ui;
}

void ChatmapperExport::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen(Qt::black, 5);
    painter.setPen(pen);
    painter.drawRect(0, 0, this->width(), this->height());
}

void ChatmapperExport::browserFile()
{
    QString jsonFilePath = QFileDialog::getOpenFileName(this,
        "Select Chatmapper export json file",
        "",
        "File (*.json)");
    if (!jsonFilePath.isEmpty())
    {
        ui->lineEdit_json_file->setText(jsonFilePath);
        Json jsonFile(jsonFilePath);
    }
}

void ChatmapperExport::exportJsonFile()
{

}
