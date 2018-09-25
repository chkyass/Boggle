#include <string>
#include <Boggle.h>

#ifndef BOGGLEPLAY_H
#define BOGGLEPLAY_H

using namespace std;

class Boggleplay {
public:
    void askForBoardGeneration(Lexicon& dictionary);
    bool playOneGame();
    void restore();

private:
    bool humanTurn = true;
    Boggle boggle;
    void askForUserBoard(string& board);
    bool onlyLetters(string s);
    bool askForWord(string& word);
    void printComputerTurn(unordered_set<string>& computerWords);
};

#endif // BOGGLEPLAY_H
