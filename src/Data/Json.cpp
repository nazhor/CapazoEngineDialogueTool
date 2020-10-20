#include "Json.h"

Json::Json(const QString& filePath)
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

void Json::readActors(QJsonValue& value)
{
    QJsonArray actorsArray = value["Actors"].toArray();
    foreach (const QJsonValue& actorValue, actorsArray)
    {
        QJsonObject obj = actorValue.toObject();
        int id = obj.value("ID").toInt();
        QJsonObject fieldsObj = obj.value("Fields").toObject();
        QString name = fieldsObj.value("Name").toString();
        Actor a(id, name);
        actors_.push_back(a);
    }
}

void Json::readConversations(QJsonValue& value)
{
    QJsonArray conversationsArray = value["Conversations"].toArray();
    foreach (const QJsonValue& conversationValue, conversationsArray)
    {
        QJsonObject convObj = conversationValue.toObject();
        int id = convObj.value("ID").toInt();
        QJsonObject fieldsObj = convObj.value("Fields").toObject();
        QString title = fieldsObj.value("Title").toString();
        QJsonValue dialogNodeValues = convObj.value("DialogNodes");
        std::vector<Node> nodes = readNodes(dialogNodeValues);
        Conversation c(id, title, nodes);
        conversations_.push_back(c);
    }
}

std::vector<Node> Json::readNodes(QJsonValue& value)
{
    std::vector<Node> nodes;
    QJsonArray dialogNodesArray = value.toArray();
    foreach (const QJsonValue& dialogNodeValue, dialogNodesArray)
    {
        QJsonObject nodeObj = dialogNodeValue.toObject();
        int id = nodeObj.value("ID").toInt();
        if (id > 0) //The first Chatmapper conversation node has no use to us
        {
            QString destinationConvIds;
            QString destinationNodeIds;
            QJsonArray outgoingLinksArray = dialogNodeValue["OutgoingLinks"].toArray();
            for (int i = 0; i < outgoingLinksArray.size(); i++)
            {
                if (i > 0)
                {
                    destinationConvIds += "-";
                    destinationNodeIds += "-";
                }
                QJsonValue outgoingLinkValue = outgoingLinksArray[i];
                QJsonObject outgoingLinkObj = outgoingLinkValue.toObject();
                int destinyConvId = outgoingLinkObj.value("DestinationConvoID").toInt();
                int destinyNodeId = outgoingLinkObj.value("DestinationDialogID").toInt();
                destinationConvIds += QString::number(destinyConvId);
                destinationNodeIds += QString::number(destinyNodeId);
            }
            QJsonObject fieldsObj = nodeObj.value("Fields").toObject();
            QString title = fieldsObj.value("Title").toString();
            int actorId = fieldsObj.value("Actor").toVariant().toInt(); //Chatmapper actor field
            QString optionText = fieldsObj.value("Menu Text").toString();
            QString dialogueText = fieldsObj.value("Dialogue Text").toString();
            bool start = fieldsObj.value("Start").toVariant().toBool();
            bool end = fieldsObj.value("End").toVariant().toBool();
            bool silence = fieldsObj.value("Silence").toVariant().toBool();
            bool multi = fieldsObj.value("Multi").toVariant().toBool();
            int change = fieldsObj.value("Change").toInt();
            bool int01Cont = fieldsObj.value("Int01Cont").toVariant().toBool();
            bool int02Nexus = fieldsObj.value("Int02Nexus").toVariant().toBool();
            bool int03Node = fieldsObj.value("Int03Node").toVariant().toBool();
            bool intNpc = fieldsObj.value("IntNpc").toVariant().toBool();

            Node node(id,
                      destinationConvIds,
                      destinationNodeIds,
                      title,
                      actorId,
                      optionText,
                      dialogueText,
                      start,
                      end,
                      silence,
                      multi,
                      change,
                      int01Cont,
                      int02Nexus,
                      int03Node,
                      intNpc
                      );
            nodes.push_back(node);
        }
    }
    return nodes;
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
    qDebug() << "--------";
    qDebug() << "-- Conversations --";
    foreach (const Conversation c, conversations_)
    {
        qDebug() << "ID: " << c.getId();
        qDebug() << "Title: " << c.getTitle();
        qDebug() << "-- Nodes --";
        foreach (const Node n, c.getNodes())
        {
            qDebug() << "ID: " << n.getId();
            qDebug() << "DestinationConv: " << n.getDestinationConvIds();
            qDebug() << "DestinationNodes: " << n.getDestinationNodeIds();
            qDebug() << "Title: " << n.getTitle();
            qDebug() << "ActorId: " << n.getActorId();
            qDebug() << "OptionText: " << n.getOptionText();
            qDebug() << "DialogueText: " << n.getDialogueText();
            qDebug() << "Start: " << n.getStart();
            qDebug() << "End: " << n.getEnd();
            qDebug() << "Silence: " << n.getSilence();
            qDebug() << "Multi: " << n.getMulti();
            qDebug() << "Change: " << n.getChange();
            qDebug() << "Int01Cont: " << n.getInt01Cont();
            qDebug() << "Int02Nexus: " << n.getInt02Nexus();
            qDebug() << "Int03Node: " << n.getInt03Node();
            qDebug() << "IntNpc: " << n.getIntNpc();
            qDebug() << "-- End node --";
        }
    }
    qDebug() << "-- End conversation --";
}
