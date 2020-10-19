#include "Node.h"

Node::Node(const int id,
           const int actorId,
           const QString& destinationConvIds,
           const QString& destinationNodeIds,
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
    actorId_ = actorId;
    destinationConvIds_ = destinationConvIds;
    destinationNodeIds_ = destinationNodeIds;
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
