#include "Validation.h"

Validation::Validation(const std::vector<Actor>& actors, const std::vector<Conversation>& conversations)
{
    actors_ = actors;
    conversations_ = conversations;
    output_ = "";
    output_ = "a\n";
    output_.append("2 ñ\n");
    output_.append("3 á\n");
    output_.append("4 |\n");
    output_.append("5 ë\n");
    output_.append("6 ô\n");
    output_.append("7 ~\n");
    output_.append("8\n");
    output_.append("9\n");
    output_.append("b\n");
    errorCounter_ = 0;
}

Validation::~Validation()
{
}

QString Validation::validate() const
{
    return output_;
}
