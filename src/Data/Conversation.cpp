#include "Conversation.h"

Conversation::Conversation(const int id, const QString& title, const std::vector<Node>& nodes)
{
    id_ = id;
    title_ = title;
    nodes_ = nodes;
}

Conversation::~Conversation()
{
}

int Conversation::getId() const
{
    return id_;
}

QString Conversation::getTitle() const
{
    return title_;
}

std::vector<Node> Conversation::getNodes() const
{
    return nodes_;
}
