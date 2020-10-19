#ifndef ACTOR_H
#define ACTOR_H

#include <QString>

class Actor
{
public:
    Actor(const int id, const QString& name);
    ~Actor();

    int getId() const;
    QString getName() const;

private:
    int id_;
    QString name_;
};

#endif // ACTOR_H
