#include <string>
#include <iostream>
#include <ctype.h>
#include "lexicon.h"
#include "console.h"
#include "boggleplay.h"

using namespace std;


void Boggleplay::restore() {
    humanTurn = true;
}

bool Boggleplay::onlyLetters(string s) {
    for (char& c : s) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

void Boggleplay::askForUserBoard(string& board) {
    do {
        cout << "Type the 16 letter to appear on the board: ";
        getline(cin, board);
    }while(board.length() != 16 || !onlyLetters(board));
}


void Boggleplay::askForBoardGeneration(Lexicon& dictionary) {
    cout << "Do you want to generate a random board ? ";
    string answer;
    string board;
    getline(cin, answer);
    if (answer[0] == 'y') {
        Boggle::getRandomBoard(board);
    } else if (answer[0] == 'n') {
        askForUserBoard(board);
    }
    this->boggle = Boggle(dictionary, board);
}

bool Boggleplay::askForWord(string& word) {
    cout << "Type a word (or Enter to stop):";
    getline(cin,word);
    if (word == "") {
        this->humanTurn = false;
        return false;
    }
    if (word.length() < 4){
        return false;
    }
    for (unsigned int i = 0; i < word.length(); i++){
        word[i] = tolower(word[i]);
    }
    return true;
}


void Boggleplay::printComputerTurn(unordered_set<string>& computerWords){

    cout << "It's computer turn !" << endl;
    cout << "Computer words (" << computerWords.size() << "): {";
    for (string word: computerWords) {
        cout << word << " ";
    }
    cout << "}" << endl;
    cout << "Computer score: " << this->boggle.getScoreComputer() << endl;

    if (this->boggle.getScoreComputer() > this->boggle.getScoreHuman()) {
        cout << "Computer is the winner !" << endl;
    } else {
        cout << "You are the winner !" << endl;
    }
}


bool Boggleplay::playOneGame() {
    if (this->humanTurn) {
        clearConsole();
        cout << this->boggle << endl;
        string word;
        if(askForWord(word)) {
            this->boggle.checkWord(word);
        }
        return false;
    } else {
        unordered_set<string> computerWords = this->boggle.computerWordSearch();
        printComputerTurn(computerWords);
        return true;
    }
}
