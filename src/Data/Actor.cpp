#include "Actor.h"

Actor::Actor(const int id, const QString& name)
{
    id_ = id;
    name_ = name;
}

Actor::~Actor()
{
}

int Actor::getId() const
{
    return id_;
}

QString Actor::getName() const
{
    return name_;
}


