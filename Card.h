//
// Created by sam on 11/12/2019.
//

#ifndef UNO_CARD_H
#define UNO_CARD_H


#include <string>

class Card {
private:

public:
    std::string card_color;

    int card_value;

    Card(std::string a, int b);

    std::string getColor();

    int getValue();

    void printCard();

    bool operator==(const Card& rhs) const;

    bool operator<(const Card& rhs) const;
};


#endif //UNO_CARD_H
