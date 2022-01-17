#include "Validation.h"

Validation::Validation(const std::vector<Actor>& actors, const std::vector<Conversation>& conversations)
{
    actors_ = actors;
    conversations_ = conversations;
    output_ = "";
    errorCounter_ = 0;
}

Validation::~Validation()
{
}

QString Validation::validate()
{
    checkDestinyNodes();
    setCabezabuqueTitle();
    return output_;
}

int Validation::getErrorCount() const
{
    return errorCounter_;
}

void Validation::setCabezabuqueTitle()
{
    if(errorCounter_ <= 5)
    {
        output_ = QString::number(errorCounter_) + " errors: Cabezon\n" + output_;
    }
    else if(errorCounter_ > 5 && errorCounter_ <= 10)
    {
        output_ = QString::number(errorCounter_) + " errors: Cabezabuque\n" + output_;
    }
    else
    {
        output_ = QString::number(errorCounter_) + " errors: Oniiii-chan\n" + output_;
    }
}

void Validation::checkDestinyNodes()
{
    for(const auto& valueConversation: conversations_)
    {
        std::vector<Node> nodes_ = valueConversation.getNodes();
        for(const auto& valueNode: nodes_)
        {
            if (valueNode.getDestinationConvIds().isEmpty() ||
                valueNode.getDestinationNodeIds().isEmpty())
            {
                if (!valueNode.getEnd())
                {
                    QString error_msg = "Conversation(" + QString::number(valueConversation.getId()) + ") node(" + QString::number(valueNode.getId()) + ") has no destination AND is no end\n";
                    output_.append(error_msg);
                    errorCounter_++;
                }
            }
            else
            {
                if (valueNode.getEnd())
                {
                    QString error_msg = "Conversation(" + QString::number(valueConversation.getId()) + ") node(" + QString::number(valueNode.getId()) + ") has destination BUT has end checked\n";
                    output_.append(error_msg);
                    errorCounter_++;
                }
            }
        }
    }
}
