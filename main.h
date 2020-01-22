//
// Created by sam on 11/13/2019.
//

#ifndef UNO_MAIN_H
#define UNO_MAIN_H

#include <string>
#include <vector>

std::string getValidName(const std::string &prompt, std::vector<std::string> names);
int getValidInt(const std::string &prompt);
std::string getValidMove(const std::string &prompt, std::string playerName);

#endif //UNO_MAIN_H
