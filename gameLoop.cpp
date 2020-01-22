//
// Created by sam on 11/13/2019.
//


#include <iostream>
#include <random>
#include <sstream>
#include <algorithm>
#include "Player.h"
#include "main.h"
#include "gameLoop.h"

//bool operator<(const Card& lhs, const Card& rhs){
//    if(lhs.card_color[0] < rhs.card_color[0]){
//        return true;
//    }
//    else if(lhs.card_color[0] == rhs.card_color[0]){
//        if(lhs.card_value < rhs.card_value){
//            return true;
//        }
//    }
//    else{
//        return false;
//    }
//}

void gameLoop(Player *currentPlayer, Card cardInPlay, std::vector<Player> &players, std::vector<Card> deck,
              std::vector<Card> discardDeck, std::minstd_rand generator, int startingHandSize, int unoCalloutPenalty,
              int badUnoCalloutPenalty, int drawLimit, bool mustPlayCardEachTurn, std::string reneging,
              bool logicGate = false) {
//    if(logicGate == false){
//        for(int i = 0; i < players.size(); i++){
//            if(players.at(i).getName() != currentPlayer.getName()){
//                std::cout << players.at(i).getName() << ": ";
//                players[i].printHand();
//            }
//        }
//        std::cout << "\n" << "Top of discard pile: " << cardInPlay.getColor() << " " << std::to_string(cardInPlay.getValue());
//        std::cout << "\n" << "Your hand: ";
//        currentPlayer.printHand();
//        std::cout << std::endl;
//    }
    for (int i = 0; i < players.size(); i++) {
        if (players.at(i).getName() != currentPlayer->getName()) {
            std::cout << players.at(i).getName() << ": ";
            std::sort(players.at(i).hand.begin(), players.at(i).hand.end());
            players[i].printHand();
        }
        if (players.size() > 2 && players.at(i).getName() != players.back().getName()) {
            std::cout << std::endl;
        }
    }
    std::cout << "\n" << "Top of discard pile: " << cardInPlay.getColor() << " "
              << std::to_string(cardInPlay.getValue());
    std::cout << "\n" << "Your hand: ";
    std::sort(currentPlayer->hand.begin(), currentPlayer->hand.end());
    currentPlayer->printHand();
    std::cout << std::endl;

    std::string playerMove = getValidMove(", enter your move or h for help: ", currentPlayer->getName());
    std::vector<std::string> playerMoveVector;
    std::istringstream ss(playerMove);
    do {
        std::string word;
        ss >> word;
        playerMoveVector.push_back(word);
    } while (ss);
    playerMoveVector.pop_back();


    if (playerMoveVector[0] == "play") {
        if (playerMoveVector.size() == 4 && playerMoveVector[3] == "uno") {
            currentPlayer->unoStatus == true;
        }
        Card playerCard = Card(playerMoveVector[1], stoi(playerMoveVector[2]));
        if (reneging == "Any" && currentPlayer->numOfDraws > 0) {
            if (playerCard.getColor() == cardInPlay.getColor() || playerCard.getValue() == cardInPlay.getValue()) {
                discardDeck.push_back(playerCard);

                auto indexOfCardToRemove = std::find(currentPlayer->hand.begin(), currentPlayer->hand.end(),
                                                     playerCard);
                if (!(indexOfCardToRemove == currentPlayer->hand.end())) { //found the card
                    std::cout << currentPlayer->getName() << " played " << playerCard.getColor() << " " << playerCard.getValue() << "." << std::endl;
                    if(currentPlayer->unoStatus == true){
                        std::cout << currentPlayer << " shouted UNO." << std::endl;
                    }
                    if(currentPlayer->unoStatus == true && currentPlayer->hand.size() > 2){
                        std::cout << "You can't call UNO unless playing your second to last card." << std::endl;
                    }
                    std::cout << std::endl;
                    currentPlayer->hand.erase(indexOfCardToRemove);
                } else {
                    std::cout << "Didnt find the card";
                }
////Check if they won the game
                if (currentPlayer->hand.size() == 0) {
                    std::cout << currentPlayer->name << " won the game" << std::endl;
                    std::cout << std::endl;
                    std::cout << "==== Leader Board ====" << std::endl;
                    for (int i = 0; i < players.size(); i++) {
                        for (int j = 0; j < players.at(i).hand.size(); j++) {
                            players.at(i).score += players.at(i).hand.at(j).getValue();
                        }
                        sort(players.begin(), players.end(), sortingPlayers);
                        std::cout << i << ".) " << players.at(i).name << " : " << players.at(i).score << std::endl;
                    }
                }

////Move on to next player
                int currentPlayerIndex = std::find(players.begin(), players.end(), *currentPlayer) - players.begin();
                if ((currentPlayerIndex + 1) == players.size()) {
                    gameLoop(&players[0], discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                             unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging);
                } else {
                    gameLoop(&players[currentPlayerIndex + 1], discardDeck.back(), players, deck, discardDeck,
                             generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit,
                             mustPlayCardEachTurn, reneging);
                }
            }
        } else if (reneging == "LastDrawn" && currentPlayer->numOfDraws > 0) {
            if ((playerCard.getColor() == cardInPlay.getColor() || playerCard.getValue() == cardInPlay.getValue()) &&
                (playerCard.getColor() == currentPlayer->cardJustDrawn.getColor() &&
                 playerCard.getValue() == currentPlayer->cardJustDrawn.getValue())) {
                discardDeck.push_back(playerCard);
                auto indexOfCardToRemove = std::find(currentPlayer->hand.begin(), currentPlayer->hand.end(),
                                                     playerCard);
                if (!(indexOfCardToRemove == currentPlayer->hand.end())) { //found the card
                    std::cout << currentPlayer->getName() << " played " << playerCard.getColor() << " " << playerCard.getValue() << "." << std::endl;
                    if(currentPlayer->unoStatus == true){
                        std::cout << currentPlayer << " shouted UNO." << std::endl;
                    }
                    if(currentPlayer->unoStatus == true && currentPlayer->hand.size() > 2){
                        std::cout << "You can't call UNO unless playing your second to last card." << std::endl;
                    }
                    std::cout << std::endl;
                    currentPlayer->hand.erase(indexOfCardToRemove);
                } else {
                    std::cout << "Didnt find the card";
                }
////Check if they won the game
                if (currentPlayer->hand.size() == 0) {
                    std::cout << currentPlayer->name << " won the game" << std::endl;
                    std::cout << std::endl;
                    std::cout << "==== Leader Board ====" << std::endl;
                    for (int i = 0; i < players.size(); i++) {
                        for (int j = 0; j < players.at(i).hand.size(); j++) {
                            players.at(i).score += players.at(i).hand.at(j).getValue();
                        }
                        sort(players.begin(), players.end(), sortingPlayers);
                        std::cout << i << ".) " << players.at(i).name << " : " << players.at(i).score << std::endl;
                    }
                }

////Move on to next player
                int currentPlayerIndex = std::find(players.begin(), players.end(), *currentPlayer) - players.begin();
                if ((currentPlayerIndex + 1) == players.size()) {
                    gameLoop(&players[0], discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                             unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging);
                } else {
                    gameLoop(&players[currentPlayerIndex + 1], discardDeck.back(), players, deck, discardDeck,
                             generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit,
                             mustPlayCardEachTurn, reneging);
                }
            } else {
////Bad input because they didnt play the last drawn card
                std::cout << "Not correct card" << std::endl;
            }
        } else {
            if (playerCard.getColor() == cardInPlay.getColor() || playerCard.getValue() == cardInPlay.getValue()) {
                discardDeck.push_back(playerCard);

//            bool operator==(const Card& lhs, const Card& rhs);
                auto indexOfCardToRemove = std::find(currentPlayer->hand.begin(), currentPlayer->hand.end(),
                                                     playerCard);
                if (!(indexOfCardToRemove == currentPlayer->hand.end())) { //found the card
                    std::cout << currentPlayer->getName() << " played " << playerCard.getColor() << " " << playerCard.getValue() << "." << std::endl;
                    if(currentPlayer->unoStatus == true){
                        std::cout << currentPlayer << " shouted UNO." << std::endl;
                    }
                    if(currentPlayer->unoStatus == true && currentPlayer->hand.size() > 2){
                        std::cout << "You can't call UNO unless playing your second to last card." << std::endl;
                    }
                    std::cout << std::endl;
//                    currentPlayer->printHand();
                    currentPlayer->hand.erase(indexOfCardToRemove);
//                    currentPlayer->printHand();
                } else {
                    std::cout << "Didnt find the card";
                }
////Check if they won the game
                if (currentPlayer->hand.size() == 0) {
                    std::cout << currentPlayer->name << " won the game" << std::endl;
                    std::cout << std::endl;
                    std::cout << "==== Leader Board ====" << std::endl;
                    for (int i = 0; i < players.size(); i++) {
                        for (int j = 0; j < players.at(i).hand.size(); j++) {
                            players.at(i).score += players.at(i).hand.at(j).getValue();
                        }
                        sort(players.begin(), players.end(), sortingPlayers);
                        std::cout << i << ".) " << players.at(i).name << " : " << players.at(i).score << std::endl;
                    }
                }

////Move on to next player
                int currentPlayerIndex = std::find(players.begin(), players.end(), *currentPlayer) - players.begin();
                if ((currentPlayerIndex + 1) == players.size()) {
                    gameLoop(&players[0], discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                             unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging);
                } else {
                    gameLoop(&players[currentPlayerIndex + 1], discardDeck.back(), players, deck, discardDeck,
                             generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit,
                             mustPlayCardEachTurn, reneging);
                }
            }
        }
    } else if (playerMoveVector[0] == "draw") {
        if (currentPlayer->numOfDraws < drawLimit) {
            currentPlayer->cardJustDrawn = deck.back();
            currentPlayer->addCardToHand(deck.back());
            deck.pop_back();
            currentPlayer->numOfDraws = currentPlayer->numOfDraws + 1;


            if (reneging == "LastDrawn" && (currentPlayer->cardJustDrawn.getColor() != cardInPlay.getColor() ||
                                            currentPlayer->cardJustDrawn.getValue() != cardInPlay.getValue())) {
                currentPlayer->numOfDraws = 0;

                int currentPlayerIndex = std::find(players.begin(), players.end(), *currentPlayer) - players.begin();
                if ((currentPlayerIndex + 1) == players.size()) {
                    gameLoop(&players[0], discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                             unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging);
                } else {
                    gameLoop(&players[currentPlayerIndex + 1], discardDeck.back(), players, deck, discardDeck,
                             generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit,
                             mustPlayCardEachTurn, reneging);
                }
            } else if (reneging == "Any") {
                bool playableCard = false;
                for (int i = 0; i < currentPlayer->hand.size(); i++) {
//                    currentPlayer->cardJustDrawn.getColor() != cardInPlay.getColor() || currentPlayer->cardJustDrawn.getValue() != cardInPlay.getValue())
                    if (currentPlayer->hand.at(i).getColor() == cardInPlay.getColor() ||
                        currentPlayer->hand.at(i).getValue() == cardInPlay.getValue()) {
                        playableCard = true;
                        break;
                    } else {
                        playableCard = false;
                    }
                }
                if (playableCard == true) {
                    gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                             unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
                } else {

                }
            } else {

            }
//            gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
        } else {
            gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                     unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
        }

    } else if (playerMoveVector[0] == "uno" || playerMoveVector[0] == "un" || playerMoveVector[0] == "u") {
        bool foundPlayer = false;
        int playerIndexForUnoCheck = 0;
        for (int i = 0; i < players.size(); i++) {

            std::string lowerCaseNameFromVector = players.at(i).name;
            transform(lowerCaseNameFromVector.begin(), lowerCaseNameFromVector.end(), lowerCaseNameFromVector.begin(), ::tolower);

            std::string lowerCaseNameFromInput = playerMoveVector[1];
            transform(lowerCaseNameFromInput.begin(), lowerCaseNameFromInput.end(), lowerCaseNameFromInput.begin(), ::tolower);


            if (lowerCaseNameFromVector == lowerCaseNameFromInput) {
                foundPlayer = true;
                playerIndexForUnoCheck = i;
            }
        }
        if (players.at(playerIndexForUnoCheck).unoStatus == true && foundPlayer == true) {
//            Apply bad uno callout to current player
            if(badUnoCalloutPenalty > 0){
                std::cout << "You had to draw " << badUnoCalloutPenalty << " cards for a bad UNO call." << std::endl;
                for (int i = 0; i < badUnoCalloutPenalty; i++) {
                    currentPlayer->addCardToHand(deck.back());
                    deck.pop_back();
                }
                gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
            }
            else{
                gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
            }
        } else if (players.at(playerIndexForUnoCheck).unoStatus == false && foundPlayer == true) {
//            apply uno callout penalty to player.at(playerIndexForUnoCheck)
            if (players.at(playerIndexForUnoCheck).hand.size() > 1) {
                std::cout << "You can't call UNO on " << players.at(playerIndexForUnoCheck).name << " because they have more than 1 card in their hand" << std::endl;
                if(badUnoCalloutPenalty > 0){
                    std::cout << "You had to draw " << badUnoCalloutPenalty << " cards for a bad UNO call." << std::endl;
                    for (int i = 0; i < badUnoCalloutPenalty; i++) {
                        currentPlayer->addCardToHand(deck.back());
                        deck.pop_back();
                    }
                }
//                std::cout << std::endl;
                gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                         unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
            } else {
                for (int i = 0; i < unoCalloutPenalty; i++) {
                    players.at(playerIndexForUnoCheck).addCardToHand(deck.back());
                    deck.pop_back();
                }
            }
        } else {
            std::cout << playerMoveVector[1] << " is not in this game." << std::endl;
            std::cout << std::endl;
            gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
        }
    } else if (playerMoveVector[0] == "skip") {
        bool playableCard;
        for (int i = 0; i < currentPlayer->hand.size(); i++) {
//                    currentPlayer->cardJustDrawn.getColor() != cardInPlay.getColor() || currentPlayer->cardJustDrawn.getValue() != cardInPlay.getValue())
            if (currentPlayer->hand.at(i).getColor() == cardInPlay.getColor() ||
                currentPlayer->hand.at(i).getValue() == cardInPlay.getValue()) {
                playableCard = true;
            } else {
                playableCard = false;
            }
        }
        if (playableCard == false || currentPlayer->numOfDraws == drawLimit) {
            int currentPlayerIndex = std::find(players.begin(), players.end(), *currentPlayer) - players.begin();
            if ((currentPlayerIndex + 1) == players.size()) {
                gameLoop(&players[0], discardDeck.back(), players, deck, discardDeck, generator, startingHandSize,
                         unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging);
            } else {
                gameLoop(&players[currentPlayerIndex + 1], discardDeck.back(), players, deck, discardDeck, generator,
                         startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn,
                         reneging);
            }
        }
    } else if (playerMoveVector[0] == "quit") {
        for (int i = 0; i < players.size(); i++) {
            players.at(i).score = 0;
            for (int j = 0; j < players.at(i).hand.size(); j++) {
                players.at(i).score += players.at(i).hand.at(j).getValue();
            }
        }
        std::sort(players.begin(), players.end(), sortingPlayers);
        std::string winnerOfGame = players[0].getName();
        std::cout << winnerOfGame << " won the game" << std::endl;
        std::cout << std::endl;
        std::cout << "==== Leader Board ====" << std::endl;
        for (int i = 0; i < players.size(); i++) {
            std::cout << i << ".) " << players.at(i).name << " : " << players.at(i).score << std::endl;
        }
    } else if (playerMoveVector[0] == "help") {
        std::cout << "\t- play card_color card_value [uno]\n";
        std::cout << "\t- draw\n";
        std::cout << "\t- uno player_name\n";
        std::cout << "\t- skip\n";
        std::cout << "\t- quit\n";
        std::cout << "\t- help\n\n";
        gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
    } else {
        std::cout << "Unknown command entered" << std::endl;
        std::cout << "\t- play card_color card_value [uno]\n";
        std::cout << "\t- draw\n";
        std::cout << "\t- uno player_name\n";
        std::cout << "\t- skip\n";
        std::cout << "\t- quit\n";
        std::cout << "\t- help\n\n";
        gameLoop(currentPlayer, discardDeck.back(), players, deck, discardDeck, generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, true);
    }
}

bool sortingPlayers(const Player a, const Player b) {
//    return (a.score < b.score);

    if(a.score < b.score){
        return true;
    }
    else if(a.score == b.score){
        std::string aName = a.name;
        std::string bName = b.name;
        transform(aName.begin(), aName.end(), aName.begin(), ::tolower);
        transform(bName.begin(), bName.end(), bName.begin(), ::tolower);
        if(aName < bName){
            return true;
        }
    }
    return false;
}

bool sortingHands(std::vector<Card> a, std::vector<Card> b) {
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            return (a.at(i).getColor() < b.at(i).getColor());
        }
    }
}
