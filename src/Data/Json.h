#ifndef JSON_H
#define JSON_H

#include <QDebug>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <vector>

#include "Data/Actor.h"
#include "Data/Conversation.h"
#include "Data/Node.h"

class Json
{
public:
    Json(const QString& filePath);
    ~Json();

    std::vector<Actor> getActors() const;
    std::vector<Conversation> getConversations() const;

private:
    QString filePath_;
    std::vector<Actor> actors_;
    std::vector<Conversation> conversations_;

    void read();
    void readActors(QJsonValue& value);
    void readConversations(QJsonValue& value);
    std::vector<Node> readNodes(QJsonValue& value);
//    void write(QJsonObject& json) const;
    void testing() const;
};

#endif // JSON_H
