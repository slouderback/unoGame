//
// Created by sam on 11/12/2019.
//

#include "Move.h"
#include "Card.h"
#include <vector>

bool validPlay(Card playerCard, Card cardInPlay) {
    return (playerCard.getColor() == cardInPlay.getColor()) || (playerCard.getValue() == cardInPlay.getValue());
}