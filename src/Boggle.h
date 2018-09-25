#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <unordered_set>
#include "lexicon.h"
using namespace std;

struct coord {
    int row;
    int col;
};


class Boggle {
public:
    static const int BOGGLE_SIZE = 4;
    Boggle();
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    unordered_set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();
    static void getRandomBoard(string& board);

    friend ostream& operator<<(ostream& out, Boggle& boggle);

private:
    int humanScore;
    int computerScore;
    Lexicon* dict;
    unordered_set <string> humanWords;
    unordered_set <string>computerWords;
    vector<coord> visited;
    char board [BOGGLE_SIZE][BOGGLE_SIZE];
    void allWordsFrom(int row, int col, string word);
    bool isPossible(int i, int j, string rest);
    bool alreadySeen(int row, int col);
};

#endif // _boggle_h
