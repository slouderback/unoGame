//
// Created by sam on 11/12/2019.
//

#include <iostream>
#include "Card.h"

Card::Card(std::string a, int b) {
    card_color = a;
    card_value = b;
}


std::string Card::getColor() {
    return card_color;
}

int Card::getValue() {
    return card_value;
}

void Card::printCard(){
    std::cout << getColor() << " " << getValue();
}

bool Card::operator==(const Card& rhs) const{
    return (this->card_color == rhs.card_color && this->card_value == rhs.card_value);
}

bool Card::operator<(const Card& rhs)const{
    if(this->card_color[0] < rhs.card_color[0]){
        return true;
    }
    else if(this->card_color[0] == rhs.card_color[0]){
        if(this->card_value < rhs.card_value){
            return true;
        }
    }
    return false;
}

//bool Card::operator<(const Card& rhs) const{
//    return(this->card_color[0] > rhs.card_color[0] && this->card_value < rhs.card_value);
//}