//
// Created by sam on 11/12/2019.
//

#include <iostream>
#include "Player.h"
#include "Card.h"

Player::Player(std::string a, std::vector<Card> b, int c, Card d, bool e, int score) {
    name = a;
    hand = b;
    numOfDraws = c;
    Card cardJustDrawn = d;
    unoStatus = e;
}


std::string Player::getName() {
    return name;
}

std::vector<Card> Player::getHand() {
    return hand;
}

void Player::printHand() {
    if(hand.size() == 1){
        std::cout << hand.at(0).getColor() << " " << std::to_string(hand.at(0).getValue());
    }
    else{
        for(int i = 0; i < hand.size()-1; i++){
            std::cout << hand.at(i).getColor() << " " << std::to_string(hand.at(i).getValue()) << ", ";
        }
        std::cout << hand.back().getColor() << " " << std::to_string(hand.back().getValue());
    }
}

void Player::addCardToHand(const Card& card) {
    hand.push_back(card);
}



bool Player::operator==(const Player& rhs) const{
    return (this->name == rhs.name);
}
