#include "Json.h"
#include "CustomWidgets/ChatmapperExport.h"

Json::Json(const QString& filePath, QWidget *parent)
{
    qInfo() << "-- create json object --";
    filePath_ = filePath;
    parent_ = (ChatmapperExport*)parent;
    gameReadyFolder_ = "GameReadyFiles";
    read();
    //testing();
}

Json::~Json()
{
}

void Json::read()
{
    QFile fileToOpen(filePath_);
    if (fileToOpen.open(QIODevice::ReadOnly))
    {
        QByteArray chatmapperBA = fileToOpen.readAll();
        QJsonDocument chatmapperDoc(QJsonDocument::fromJson(chatmapperBA));
        QJsonObject chatmapperObj = chatmapperDoc.object();
        QJsonValue assetValues = chatmapperObj.value("Assets");
        readActors(assetValues);
        readConversations(assetValues);
        fileToOpen.close();

        qDebug() << "file: " << filePath_;
        int initS = filePath_.lastIndexOf("/") + 1;
        int endS = filePath_.lastIndexOf(".json");
        fileName_ = filePath_.mid(initS, endS - initS);
        qDebug() << "file name: " << fileName_;
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

void Json::save()
{
    write();
}

void Json::write()
{
    if (!QDir(gameReadyFolder_).exists())
    {
        QDir().mkdir(gameReadyFolder_);
    }
    QFile saveJsonFile(gameReadyFolder_ + "/" + fileName_ + ".json");
    QFile saveCsvFile(gameReadyFolder_ + "/" + fileName_ + ".csv");
    QFile saveCppFile(gameReadyFolder_ + "/" + fileName_ + ".cpp");

    if (saveJsonFile.open(QIODevice::WriteOnly) && saveCsvFile.open(QIODevice::WriteOnly) && saveCppFile.open(QIODevice::WriteOnly))
    {
        QJsonObject gameObj;

        //Add actor to the json file. Disabled because it's more useful to create a .cpp with the lines to copy in the Unreal .cpp class
//        QJsonArray actorsArray;
//        foreach (const Actor actor, actors_)
//        {
//            QJsonObject actorObj;
//            actorObj["id"] = actor.getId();
//            actorObj["name"] = actor.getName();
//            actorsArray.append(actorObj);
//        }
//        gameObj["actors"] = actorsArray;
        //Create the cpp with actors
        QTextStream streamCpp(&saveCppFile);
        addActorsToCpp(streamCpp);
        streamCpp << "\n";
        addConversationsToCpp(streamCpp);
        saveCppFile.close();






        //CSV
        QTextStream streamCsv(&saveCsvFile);
        streamCsv << "conversationId" << "\t" << "nodeId" << "\t" << "optionText_ES" << "\t" << "dialogueText_ES" << "\t" << "optionText_EN" << "\t" << "dialogueText_EN" << "\n";

        QJsonArray conversationsArray;
        foreach (const Conversation conversation, conversations_)
        {
            QJsonObject conversationObj;
            conversationObj["id"] = conversation.getId();
            conversationObj["title"] = conversation.getTitle();            
            QJsonArray nodesArray;
            foreach (const Node node, conversation.getNodes())
            {
                QJsonObject nodeObj;
                nodeObj["id"] = node.getId();
                nodeObj["destinationConvIds"] = node.getDestinationConvIds();
                nodeObj["destinationNodeIds"] = node.getDestinationNodeIds();
//                El campo title lo comento que no tiene ningún uso en UE4
//                nodeObj["title"] = node.getTitle();
                nodeObj["actorId"] = node.getActorId();
                nodeObj["optionText"] = node.getOptionText();
                nodeObj["dialogueText"] = node.getDialogueText();
                nodeObj["start"] = node.getStart();
                nodeObj["end"] = node.getEnd();
                if (parent_->silence->getCheckStatus())
                {
                    nodeObj["silence"] = node.getSilence();
                }
                if (parent_->multi->getCheckStatus())
                {
                    nodeObj["multi"] = node.getMulti();
                }
                if (parent_->change->getCheckStatus())
                {
                    nodeObj["change"] = node.getChange();
                }
                if (parent_->int01Cont->getCheckStatus())
                {
                    nodeObj["int01Cont"] = node.getInt01Cont();
                }
                if (parent_->int02Nexus->getCheckStatus())
                {
                    nodeObj["int02Nexus"] = node.getInt02Nexus();
                }
                if (parent_->int03Node->getCheckStatus())
                {
                    nodeObj["int03Node"] = node.getInt03Node();
                }
                if (parent_->intNpc->getCheckStatus())
                {
                    nodeObj["intNpc"] = node.getIntNpc();
                }
                nodesArray.append(nodeObj);

                streamCsv << conversation.getId() << "\t" << node.getId() << "\t" << "\"" << node.getOptionText() << "\"" << "\t" << "\"" << node.getDialogueText() << "\"" << "\n";
            }
            conversationObj["nodes"] = nodesArray;
            conversationsArray.append(conversationObj);
        }
        gameObj["conversations"] = conversationsArray;

        QJsonDocument gameDoc(gameObj);
        saveJsonFile.write(gameDoc.toJson());
        saveJsonFile.close();
        saveCsvFile.close();
    }
    else
    {
    }
}

void Json::testing() const
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

std::vector<Actor> Json::getActors() const
{
    return actors_;
}

std::vector<Conversation> Json::getConversations() const
{
    return conversations_;
}

void Json::addActorsToCpp(QTextStream& streamCpp) const
{
    streamCpp << "//Actors map" << "\n";
    streamCpp << "UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = \"Capazo\")" << "\n";
    streamCpp << "    TMap<FString, int32> ActorIdsMap;" << "\n";
    streamCpp << "\n";
    foreach (const Actor actor, actors_)
    {
        QString id = QString::number(actor.getId());
        streamCpp << "ActorsMap.Add(\"" + actor.getName() + "\", " + id + ");" << "\n";
    }
    streamCpp << "\n";
    streamCpp << "//Actors enums, revisa las COMMAS" << "\n";
    streamCpp << "UENUM(BlueprintType)" << "\n";
    streamCpp << "enum class EActors : uint8" << "\n";
    streamCpp << "{ " << "\n";
    foreach (const Actor actor, actors_)
    {
        streamCpp << "    " << actor.getName() << " UMETA(DisplayName = \"" + actor.getName() + "\")," << "\n";
    }
    streamCpp << "}; " << "\n";
}

void Json::addConversationsToCpp(QTextStream& streamCpp) const
{
    streamCpp << "//Conversations map" << "\n";
    streamCpp << "UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = \"Capazo\")" << "\n";
    streamCpp << "    TMap<FString, int32> ConversationIdsMap;" << "\n";
    streamCpp << "\n";
    foreach (const Conversation conversation, conversations_)
    {
        QString id = QString::number(conversation.getId());
        streamCpp << "ConversationIdsMap.Add(\"" + conversation.getTitle() + "\", " + id + ");" << "\n";
    }
    streamCpp << "\n";
    streamCpp << "//Conversations enums, revisa las COMMAS" << "\n";
    streamCpp << "UENUM(BlueprintType)" << "\n";
    streamCpp << "enum class EConversations : uint8" << "\n";
    streamCpp << "{ " << "\n";
    foreach (const Conversation conversation, conversations_)
    {
        streamCpp << "    " << conversation.getTitle() << " UMETA(DisplayName = \"" + conversation.getTitle() + "\")," << "\n";
    }
    streamCpp << "}; " << "\n";
}
