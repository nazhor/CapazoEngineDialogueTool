#include "Conversation.h"

Conversation::Conversation(const int id, const QString title)
{
    id_ = id;
    title_ = title;
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
