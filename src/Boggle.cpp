#include <algorithm>
#include <chrono>
#include <random>
#include <cctype>
#include "Boggle.h"

static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

void Boggle::getRandomBoard(string& board) {
    for (string& cube: CUBES) {
        long long seed = std::chrono::system_clock::now().time_since_epoch().count();

        shuffle(cube.begin(), cube.end(), std::default_random_engine(static_cast<unsigned int>(seed)));
        board += cube[0];
    }
}

Boggle::Boggle(){}

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    this->dict = &dictionary;
    for(int i = 0; i < this->BOGGLE_SIZE; i++) {
        for(int j = 0; j < this->BOGGLE_SIZE; j++) {
            this->board[i][j] = tolower(boardText[this->BOGGLE_SIZE*i + j]);
        }
    }
    this->humanScore = 0;
    this->computerScore = 0;
}

char Boggle::getLetter(int row, int col) {
    if (row < 0 || row >= BOGGLE_SIZE) {
        throw row;
    }
    if (col < 0 || col >= BOGGLE_SIZE) {
        throw col;
    }
    return this->board[row][col];
}

bool Boggle::checkWord(string word) {
    if (word.length() >= 4 && humanWordSearch(word)
            && this->dict->contains(word)
            && this->humanWords.find(word) == humanWords.end()) {
        this->humanWords.insert(word);
        this->humanScore += word.size() - 3;
        return true;
    }
    return false;
}

bool Boggle::isPossible(int row, int col, string rest) {
    if (row < 0 || col < 0 || row >= BOGGLE_SIZE || col >= BOGGLE_SIZE) {
        return false;
    }else if (alreadySeen(row, col)){
        return false;

    }else if (rest[0] == this->board[row][col]) {
        rest.erase(0, 1);
        if (rest == ""){
            return true;
        }
        bool result = false;
        coord c = {row, col};
        this->visited.push_back(c);
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
               result = result || isPossible(row+i, col+j, rest);
            }
        }
        this->visited.pop_back();
        return result;
    }

    return false;
}


bool Boggle::alreadySeen(int row, int col){
    for (coord& c : this->visited){
        if(c.row == row && c.col == col){
            return true;
        }
    }
    return false;
}

void Boggle::allWordsFrom(int row, int col, string word) {
    if (row < 0 || col < 0 || row >= BOGGLE_SIZE || col >= BOGGLE_SIZE) {
        return;
    }else if (alreadySeen(row, col)) {
        return;

    }else if (word.length() >= 4 && this->dict->contains(word) && this->computerWords.find(word) == computerWords.end()) {
        this->computerWords.insert(word);
        this->computerScore += word.length() - 3;
    }

    word += this->board[row][col];
    if (this->dict->containsPrefix(word)) {
        coord c = {row, col};
        this->visited.push_back(c);
        for (int i = -1; i <=1; i++) {
            for (int j = -1; j <=1; j++) {
                allWordsFrom(row+i, col+j, word);
            }
        }
        this->visited.pop_back();
    }
}


bool Boggle::humanWordSearch(string word) {
    for (int i = 0; i < BOGGLE_SIZE; i++) {
        for (int j = 0; j < BOGGLE_SIZE; j++) {
            if (word[0] == this->board[i][j]) {

                if (isPossible(i, j, word)) {
                    return true;
                }
            }
        }
    }
    return false;
}

int Boggle::getScoreHuman() { 
    return this->humanScore;
}

unordered_set<string> Boggle::computerWordSearch() {
    for (int i = 0; i < BOGGLE_SIZE; i++) {
        for (int j = 0; j < BOGGLE_SIZE; j++) {

            allWordsFrom(i, j, "");
        }
    }
    return this->computerWords;
}

int Boggle::getScoreComputer() {
    return this->computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    cout << "You must enter an unfound 4+ letter word from the dictionary." << endl;
    for (int i = 0; i < Boggle::BOGGLE_SIZE; i++) {
        for (int j = 0; j < Boggle::BOGGLE_SIZE; j++) {
            out << boggle.getLetter(i, j);
        }
        out << endl;
    }
    out << endl;
    out << "Your words (" << boggle.humanWords.size() << "): {";
    for (auto it = boggle.humanWords.begin(); it != boggle.humanWords.end(); ++it) {
        out << *it << " ";
    }
    out << "}" << endl;
    out << "Your score: " << boggle.humanScore << endl;
    return out;
}
