#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <random>
#include "Card.h"
#include "Player.h"
#include "gameLoop.h"
#include "main.h"


int main(int argc, char **argv) {

    std::vector<std::string> inputFile;
    std::string str;
    std::ifstream fin(argv[1]);
    while (fin >> str) {
        inputFile.push_back(str);
    }
    fin.close(); // Close that file!



    std::vector<Card> deck;
    for (int i = 0; i < inputFile.size(); i++){
        if((i%3) == 0){
            for(int j = 0; j < stoi(inputFile[i]); j++){
                deck.push_back(Card(inputFile[i+1], stoi(inputFile[i+2])));
            }
        }
    }
    std::vector<Card> discardDeck;


    std::vector<std::string> rulesFile;
    std::ifstream file(argv[2]);
    std::string line;

    std::vector<std::vector<std::string>> allRules;
    std::vector<std::string> singleRuleLine;

    while(std::getline(file, line)) {
        rulesFile.push_back(line);
    }
    for(int i = 0; i < rulesFile.size(); i++){
//        std::cout << rulesFile.at(i) << std::endl;
        std::istringstream ss(rulesFile.at(i));
        // Traverse through all words
        do {
            // Read a word
            std::string word;
            ss >> word;

            // Print the read word
//            std::cout << word << std::endl;
            singleRuleLine.push_back(word);

            // While there is more to read
        } while (ss);
        allRules.push_back(singleRuleLine);
        singleRuleLine.clear();
    }
    for(int i = 0; i < allRules.size(); i++){
        allRules.at(i).pop_back();
    }

    int seed;
////  If no val is passed in
    if(argc == 3){
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    else{
        seed = std::stoi(argv[3]);
    }
    std::minstd_rand generator(seed);

    std::shuffle(deck.begin(), deck.end(), generator);
////    Testing post shuffle
//    for(int i = 0; i < deck.size(); i++){
//        deck.at(i).printCard();
//        std::cout << std::endl;
//    }

    int startingHandSize = stoi(allRules.at(0).at(2));
    int unoCalloutPenalty = stoi(allRules.at(1).at(2));
    int badUnoCalloutPenalty = stoi(allRules.at(2).at(2));
    int drawLimit = stoi(allRules.at(3).at(2));
    bool mustPlayCardEachTurn;
    if(allRules.at(4).at(2) == "true"){
        mustPlayCardEachTurn = true;
    }
    else{
        mustPlayCardEachTurn = false;
    }
    std::string reneging = allRules.at(5).at(2);




//    for(int i = 0; i < deck.size(); i++){
//        deck[i].printCard();
//        std::cout << "\n";
//    }

////Working players with extra testing added on
    std::vector<Player> players;
    std::vector<std::string> names;
    int numOfPlayers = getValidInt("Enter the number of players in the game: ");
    for(int i = 0; i < numOfPlayers; i++){
        std::string result = "Player " + std::to_string(i+1) + " enter your name: ";
//        names.push_back(getValidName(result));
        std::string inputName = getValidName(result, names);
        names.push_back(inputName);
    }
    for(int i = 0; i < names.size(); i++){
        players.push_back(Player(names.at(i), std::vector<Card>()));
    }

////    Testing
//    players[0].addCardToHand(Card("Blue", 7));
//    players[0].addCardToHand(Card("Red", 7));
//    players[1].addCardToHand(Card("Yellow", 3));
//    players[1].addCardToHand(Card("Green", 3));
//    gameLoop(players[0], Card("Purple", 1), players, generator);
////    Testing end


//    std::cout << numOfPlayers*startingHandSize << " " << deck.size();
    if((numOfPlayers*startingHandSize) >= deck.size()){
//        Distribute cards evenly
//        std::cout << "gotta write this out";
        while ((deck.size()-1) > players.size()) {
            for (int i = 0; i < players.size() && (deck.size()-1) > players.size(); i++) {
                players.at(i).addCardToHand(deck.back());
                deck.pop_back();
            }
        }
    }
    else{
        for(int i = 0; i < startingHandSize; i++){
            for(int j = 0; j < players.size(); j++){
                players.at(j).addCardToHand(deck.back());
                deck.pop_back();
            }
        }
    }

//////  Print out the initial hand dealt
//    for(int i = 0; i < players.size(); i++){
//        std::cout << players.at(i).getName() << ": ";
//        players.at(i).printHand();
//        std::cout << std::endl;
//    }
    discardDeck.push_back(deck.back());
    deck.pop_back();
    gameLoop(&players[0], discardDeck.back(), players, deck, discardDeck, generator, startingHandSize, unoCalloutPenalty, badUnoCalloutPenalty, drawLimit, mustPlayCardEachTurn, reneging, false);

//TODO: Work on getting a valid move

    return 0;
}


bool StreamOnlyContainsWhiteSpace(std::istream &stream) {
    char c = '!';
    if (!stream) { //if you can't read from the stream
        return false; //something is wrong with the stream
    } else {
        stream >> c; // attempt to read a nonwhitespace character
        //if the stream is bad it means we failed to read
        //and we should since there shouldn't be anything left
        return !stream;
    }
}

std::string getValidName(const std::string &prompt, std::vector<std::string> names) {
    std::string lineRead;
    std::string val;
    std::string originalName;
    std::vector<std::string> copy = names;
    bool readSuccessful = false;
    do {
        std::cout << prompt;
        std::getline(std::cin, lineRead); // grab the line
        std::stringstream lineParser(lineRead); //put it into a string stream so we can parse it
        lineParser >> val; //read what we want
        originalName = val;
        for(int i = 0; i < copy.size(); i++){
            std::for_each(copy.at(i).begin(), copy.at(i).end(), [](char &c) {
                c = ::tolower(c);
            });
        }
        std::for_each(val.begin(), val.end(), [](char &c) {
            c = ::tolower(c);
        });
        readSuccessful = StreamOnlyContainsWhiteSpace(lineParser); //check that there isn't anything left
    } while (!readSuccessful || (std::find(copy.begin(), copy.end(), val)) != copy.end()); //keep asking until they give me what I want
    return originalName;
}

int getValidInt(const std::string &prompt) {
    std::string lineRead;
    int val;
    bool readSuccessful = false;
    do {
        std::cout << prompt;
        std::getline(std::cin, lineRead); // grab the line
        std::stringstream lineParser(lineRead); //put it into a string stream so we can parse it
        lineParser >> val; //read what we want
        readSuccessful = StreamOnlyContainsWhiteSpace(lineParser); //check that there isn't anything left
    } while (!readSuccessful || val < 2); //keep asking until they give me what I want
    return val;
}

std::string getValidMove(const std::string &prompt, std::string playerName) {
//    std::string lineRead;
//    std::string val;
//    bool readSuccessful = false;
//    do {
//        std::cout << playerName << prompt;
//        std::getline(std::cin, lineRead); // grab the line
//        std::stringstream lineParser(lineRead); //put it into a string stream so we can parse it
//        lineParser >> val; //read what we want
//        std::for_each(val.begin(), val.end(), [](char &c) {
//            c = ::tolower(c);
//        });
//        readSuccessful = StreamOnlyContainsWhiteSpace(lineParser); //check that there isn't anything left
//    } while (!readSuccessful); //keep asking until they give me what I want
    std::string lineRead;
    std::vector<std::string> moveWords;

    std::cout << playerName << prompt;
    std::getline(std::cin, lineRead); // grab the line
    std::string unFormattedLineRead = lineRead;
    std::for_each(lineRead.begin(), lineRead.end(), [](char &c) {
        c = ::tolower(c);
    });
    std::istringstream ss(lineRead);
    do {
        // Read a word
        std::string word;
        ss >> word;

        moveWords.push_back(word);
//        std::cout << word << std::endl;

        // While there is more to read
    } while (ss);
    moveWords.pop_back();

//TODO: MAKE ALL CARD COLORS WORK
    if(moveWords[0][0] == 'p'){
//        if(moveWords.size() == 3){
        if(moveWords.size() == 3 && (moveWords[2][0] =='0' || moveWords[2][0] == '1' || moveWords[2][0] == '2' || moveWords[2][0] == '3' || moveWords[2][0] == '4' || moveWords[2][0] == '5' || moveWords[2][0] == '6' || moveWords[2][0] == '7' || moveWords[2][0] == '8' || moveWords[2][0] == '9')){
            if(moveWords[1][0] == 'r'){
                std::string play = "play Red ";
                play += moveWords[2][0];
                return play;
            }
            if(moveWords[1][0] == 'g'){
                std::string play = "play Green ";
                play += moveWords[2][0];
                return play;
            }
            if(moveWords[1][0] == 'b'){
                std::string play = "play Blue ";
                play += moveWords[2][0];
                return play;
            }
            if(moveWords[1][0] == 'y'){
                std::string play = "play Yellow ";
                play += moveWords[2][0];
                return play;
            }
        }
        else if(moveWords[3] == "uno" && moveWords.size() == 4){
            if(moveWords[1][0] == 'r'){
                std::string play = "play Red ";
                play += moveWords[2][0];
                play += " uno";
                return play;
            }
            if(moveWords[1][0] == 'g'){
                std::string play = "play Green ";
                play += moveWords[2][0];
                play += " uno";
                return play;
            }
            if(moveWords[1][0] == 'b'){
                std::string play = "play Blue ";
                play += moveWords[2][0];
                play += " uno";
                return play;
            }
            if(moveWords[1][0] == 'y'){
                std::string play = "play Yellow ";
                play += moveWords[2][0];
                play += " uno";
                return play;
            }
        }
        else{
            return "Unknown command entered";
        }
    }
    else if(moveWords[0][0] == 'd' && moveWords.size() == 1){
        return "draw";
    }
    else if(moveWords[0][0] == 'u' && moveWords.size() == 2){
        return unFormattedLineRead;
    }
    else if(moveWords[0][0] == 's' && moveWords.size() == 1){
        return "skip";
    }
    else if(moveWords[0][0] == 'q' && moveWords.size() == 1){
        return "quit";
    }
    else if(moveWords[0][0] == 'h' && moveWords.size() == 1){
        return "help";
    }
    else{
        return "Unknown command entered";
    }
}
