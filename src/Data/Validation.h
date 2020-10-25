#ifndef VALIDATION_H
#define VALIDATION_H

#include <QString>
#include <QTextStream>
#include <vector>

#include "Data/Actor.h"
#include "Data/Conversation.h"
#include "Data/Node.h"

class Validation
{
public:
    Validation(const std::vector<Actor>& actors, const std::vector<Conversation>& conversations);
    ~Validation();

    QString validate() const;

private:
    std::vector<Actor> actors_;
    std::vector<Conversation> conversations_;
    QString output_;
    int errorCounter_;

};

#endif // VALIDATION_H
