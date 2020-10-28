#ifndef JSON_H
#define JSON_H

#include <QDebug>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <vector>

#include "Data/Actor.h"
#include "Data/Conversation.h"
#include "Data/Node.h"

class ChatmapperExport;

class Json
{
public:
    Json(const QString& filePath, QWidget* parent);
    ~Json();

    void save();

    std::vector<Actor> getActors() const;
    std::vector<Conversation> getConversations() const;

private:
    QString filePath_;
    ChatmapperExport *parent_;
    std::vector<Actor> actors_;
    std::vector<Conversation> conversations_;
    QString gameReadyFolder_;

    void read();
    void readActors(QJsonValue& value);
    void readConversations(QJsonValue& value);
    std::vector<Node> readNodes(QJsonValue& value);    
    void write();
    void testing() const;
};

#endif // JSON_H
