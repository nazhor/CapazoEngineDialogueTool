#include "ChatmapperExport.h"
#include "ui_ChatmapperExport.h"

ChatmapperExport::ChatmapperExport(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatmapperExport)
{
    ui->setupUi(this);

    parent_ = (MainWindow*)parent;


//    Por si en un futuro esto es una ventana dentro de una app más grande
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
    ui->groupBox_output_log->setPalette(palf);
    ui->groupBox_custom_fields->setPalette(palf);

    addCustomFields();
    addGames();

    connect(ui->pushButton_browser_file, SIGNAL(released()), this, SLOT(browserFile()));
    connect(ui->pushButton_export_json, SIGNAL(released()), this, SLOT(exportJsonFile()));
    connect(ui->comboBox_select_game, SIGNAL(currentIndexChanged(int)), this, SLOT(selectGame(int)));
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
        jsonFile_ = new Json(jsonFilePath, this);

        QFile fileToOpen(":/files/CustomFields");
        if (fileToOpen.open(QIODevice::ReadOnly))
        {
            QTextStream customFields(&fileToOpen);
            QString customFieldsRead = customFields.readAll();            
            fileToOpen.close();
        }        

        ui->pushButton_export_json->setEnabled(true);
    }
}

void ChatmapperExport::exportJsonFile()
{
    Validation v(jsonFile_->getActors(), jsonFile_->getConversations());
    QString validationResult = v.validate();
    int validationErrorCount = v.getErrorCount();
    ResultDialog *result;
    if (validationErrorCount == 0)
    {
        result = new ResultDialog(true, this);
        ui->plainTextEdit_output_log->setPlainText("No errors");
        jsonFile_->save();
    }
    else
    {
        result = new ResultDialog(false, this);
        QFile file("errors.log");
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.write(validationResult.toUtf8());
        }
        file.close();
        ui->plainTextEdit_output_log->setPlainText(validationResult);
    }
    if (result->exec() == QDialog::Accepted)
    {

    }
}

void ChatmapperExport::addCustomFields()
{
    silence = new CustomField("Silence");
    multi = new CustomField("Multispeech");
    change = new CustomField("Change of mind");
    int01Cont = new CustomField("Int. Continue");
    int02Nexus = new CustomField("Int. Nexus");
    int03Node = new CustomField("Int. Node");
    intNpc = new CustomField("Int. Npc");

    ui->verticalLayout_custom_fields->addWidget(silence);
    ui->verticalLayout_custom_fields->addWidget(multi);
    ui->verticalLayout_custom_fields->addWidget(change);
    ui->verticalLayout_custom_fields->addWidget(int01Cont);
    ui->verticalLayout_custom_fields->addWidget(int02Nexus);
    ui->verticalLayout_custom_fields->addWidget(int03Node);
    ui->verticalLayout_custom_fields->addWidget(intNpc);
}

void ChatmapperExport::addGames()
{
    gamesMap = new QMap<int, QString>;
    gamesMap->insert(0, "Custom");
    gamesMap->insert(1, "Temazo");
    gamesMap->insert(2, "I need a drink");

    QMap<int, QString>::iterator it;
    for (it = gamesMap->begin(); it != gamesMap->end(); ++it)
    {
        ui->comboBox_select_game->addItem(it.value());
    }
}

void ChatmapperExport::selectGame(const int index)
{
    switch (index)
    {
        case 0: //Custom
        case 2: //I need a drink
            silence->setCheckStatus(true);
            multi->setCheckStatus(true);
            change->setCheckStatus(true);
            int01Cont->setCheckStatus(true);
            int02Nexus->setCheckStatus(true);
            int03Node->setCheckStatus(true);
            intNpc->setCheckStatus(true);
            break;
        case 1: //Temazo
            silence->setCheckStatus(true);
            multi->setCheckStatus(false);
            change->setCheckStatus(false);
            int01Cont->setCheckStatus(false);
            int02Nexus->setCheckStatus(false);
            int03Node->setCheckStatus(false);
            intNpc->setCheckStatus(false);
            break;
        break;        
    }
}
