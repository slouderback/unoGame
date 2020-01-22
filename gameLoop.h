//
// Created by sam on 11/13/2019.
//

#ifndef UNO_GAMELOOP_H
#define UNO_GAMELOOP_H

#include "Player.h"

void gameLoop(Player *currentPlayer, Card cardInPlay, std::vector<Player> &players, std::vector<Card> deck, std::vector<Card> discardDeck, std::minstd_rand generator, int startingHandSize, int unoCalloutPenalty, int badUnoCalloutPenalty, int drawLimit, bool mustPlayCardEachTurn, std::string reneging, bool logicGate);

bool sortingPlayers(const Player a, const Player b);

bool sortingHands(std::vector<Card> a, std::vector<Card> b);

//bool operator<(const Card& lhs, const Card& rhs);

#endif //UNO_GAMELOOP_H
