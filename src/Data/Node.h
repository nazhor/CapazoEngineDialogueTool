#ifndef NODE_H
#define NODE_H

#include <QString>

class Node
{
public:
    Node(const int id,
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
         );
    ~Node();

private:
    int id_;
    int actorId_;
    QString destinationConvIds_; //String with conversation Ids. Format X_Y_Z
    QString destinationNodeIds_; //String with node Ids. Format X_Y_Z
    QString optionText_; //The answer text displayed to the player
    QString dialogueText_; //The actual dialogue text once an option was selected
    bool start_; //First node of the conversation
    bool end_; //Conversation end
    bool silence_; //Silence node (no dialogue text, hidden option)
    bool multi_; //The dialogueText has more than one text with the same meaning (for looping)
    int change_; //The node could be replaced by another one when triggered
    bool int01Cont_; //Interruption that continues without changing the subject. NPC continues talking ignoring the player.
    bool int02Nexus_; //Interruption that "loops" the npc. He shuts up, lets player speak and continues with a nexus like "...as I was saying..."
    bool int03Node_; //Interruption that changes the subject. NPC shuts up and listen to the player and then answers accordingly.
    bool intNpc_; //The NPC interrupts the player

};

#endif // NODE_H
