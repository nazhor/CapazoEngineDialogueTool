#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QString>
#include <vector>

#include "Node.h"

class Conversation
{
public:
    Conversation(const int id, const QString& title);
    ~Conversation();

    int getId() const;
    QString getTitle() const;

private:
    int id_;
    QString title_;
    std::vector<Node> nodes_;

};

#endif // CONVERSATION_H
