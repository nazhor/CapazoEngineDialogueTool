#include "Json.h"

Json::Json(const QString filePath)
{
    qInfo() << "-- create json object --";
    filePath_ = filePath;
    read();
    testing();
}

Json::~Json()
{
}

void Json::read()
{
    QFile fileToOpen(filePath_);
    if (fileToOpen.open(QIODevice::ReadOnly))
    {
        QTextStream chatmapper(&fileToOpen);
        QString chatmapperString = chatmapper.readAll();
        fileToOpen.close();

        QJsonDocument chatmapperDoc = QJsonDocument::fromJson(chatmapperString.toUtf8());
        QJsonObject chatmapperObj = chatmapperDoc.object();
        QJsonValue assetValues = chatmapperObj.value("Assets");
        readActors(assetValues);
        readConversations(assetValues);
    }

}

void Json::readActors(QJsonValue &value)
{
    QJsonArray actorsArray = value["Actors"].toArray();
    foreach (const QJsonValue & actorValue, actorsArray)
    {
        QJsonObject obj = actorValue.toObject();
        int id = obj.value("ID").toInt();
        QJsonObject fieldsObj = obj.value("Fields").toObject();
        QString name = fieldsObj.value("Name").toString();
        Actor a(id, name);
        actors_.push_back(a);
    }
}

void Json::readConversations(QJsonValue &value)
{
    QJsonArray conversationsArray = value["Conversations"].toArray();
    foreach (const QJsonValue & conversationValue, conversationsArray)
    {
        QJsonObject obj = conversationValue.toObject();
        int id = obj.value("ID").toInt();
        QJsonObject fieldsObj = obj.value("Fields").toObject();
        QString title = fieldsObj.value("Title").toString();
        Conversation c(id, title);
        conversations_.push_back(c);
    }
}

//void Json::write(QJsonObject& json) const
//{

//}

void Json::testing()
{
    qDebug() << "-- Actors --";
    foreach (const Actor a, actors_)
    {
        qDebug() << "ID: " << a.getId();
        qDebug() << "Name: " << a.getName();
    }
    qDebug() << "-- Conversations --";
    foreach (const Conversation c, conversations_)
    {
        qDebug() << "ID: " << c.getId();
        qDebug() << "Title: " << c.getTitle();
    }

}
