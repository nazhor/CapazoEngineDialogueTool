#include "ChatmapperExport.h"
#include "ui_ChatmapperExport.h"

ChatmapperExport::ChatmapperExport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatmapperExport)
{
    ui->setupUi(this);

    parent_ = (MainWindow*)parent;


//    const int widgetPercentWidtch = 30;
//    int widgetWidth = MainWindow::getWindowWidth() * widgetPercentWidtch / 100;
//    const int widgetPercentHeight = 70;
//    int widgetHeight = MainWindow::getWindowHeight() * widgetPercentHeight / 100;
//    int widgetX = (MainWindow::getWindowWidth() / 2) - (widgetWidth / 2);
//    int widgetY = (MainWindow::getWindowHeight() / 2) - (widgetHeight / 2);
//    this->setGeometry(widgetX,
//                      widgetY,
//                      widgetWidth,
//                      widgetHeight);


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
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);
//    QPen pen(Qt::black, 5);
//    painter.setPen(pen);
//    painter.drawRect(0, 0, this->width(), this->height());
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
        jsonFile_ = new Json(jsonFilePath);
        ui->pushButton_export_json->setEnabled(true);
    }
}

void ChatmapperExport::exportJsonFile()
{
    Validation v(jsonFile_->getActors(), jsonFile_->getConversations());
    QString validationResult = v.validate();
    ResultDialog *result;
    if (validationResult.isEmpty())
    {
        result = new ResultDialog(true, this);
    }
    else
    {
        result = new ResultDialog(false, this);
        QFile file("errors.log");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(validationResult.toUtf8());
        }
        file.close();
    }
    if (result->exec() == QDialog::Accepted)
    {

    }
}
