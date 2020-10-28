#include "Node.h"

Node::Node(
           const int id,
           const QString& destinationConvIds,
           const QString& destinationNodeIds,
           const QString& title,
           const int actorId,
           const QString& optionText,
           const QString& dialogueText,
           const bool start,
           const bool end,
           const bool silence,
           const bool multi,
           const int change,
           const bool int01Cont,
           const bool int02Nexus,
           const bool int03Node,
           const bool intNpc
        )
{
    id_ = id;
    destinationConvIds_ = destinationConvIds;
    destinationNodeIds_ = destinationNodeIds;
    title_ = title,
    actorId_ = actorId;
    optionText_ = optionText;
    dialogueText_ = dialogueText;
    start_ = start;
    end_ = end;
    silence_ = silence;
    multi_ = multi;
    change_ = change;
    int01Cont_ = int01Cont;
    int02Nexus_ = int02Nexus;
    int03Node_ = int03Node;
    intNpc_ = intNpc;
}

Node::~Node()
{
}

int Node::getId() const
{
    return id_;
}

QString Node::getDestinationConvIds() const
{
    return destinationConvIds_;
}

QString Node::getDestinationNodeIds() const
{
    return destinationNodeIds_;
}

QString Node::getTitle() const
{
    return title_;
}

int Node::getActorId() const
{
    return actorId_;
}

QString Node::getOptionText() const
{
    return optionText_;
}

QString Node::getDialogueText() const
{
    return dialogueText_;
}

bool Node::getStart() const
{
    return start_;
}

bool Node::getEnd() const
{
    return end_;
}

bool Node::getSilence() const
{
    return silence_;
}

bool Node::getMulti() const
{
    return multi_;
}

int Node::getChange() const
{
    return change_;
}

bool Node::getInt01Cont() const
{
    return int01Cont_;
}

bool Node::getInt02Nexus() const
{
    return int02Nexus_;
}

bool Node::getInt03Node() const
{
    return int03Node_;
}

bool Node::getIntNpc() const
{
    return intNpc_;
}
