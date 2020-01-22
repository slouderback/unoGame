//
// Created by sam on 11/12/2019.
//

#ifndef UNO_PLAYER_H
#define UNO_PLAYER_H


#include <vector>
#include <string>
#include "Card.h"

class Player {
public:
    std::string name;

    std::vector<Card> hand;

    int numOfDraws;

    Card cardJustDrawn = Card("Empty", 0);

    bool unoStatus;

    int score;

    Player(std::string a, std::vector<Card> b, int c=0, Card d = Card("Empty", 0), bool e = false, int score = 0);

    std::string getName();

    std::vector<Card> getHand();

    void addCardToHand(const Card& card);

    void printHand();

    bool operator==(const Player& rhs) const;
};



#endif //UNO_PLAYER_H
