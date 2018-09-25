#include <fstream>
#include <iostream>
#include <string>
#include "simpio.h"
#include "boggleplay.h"

using namespace std;

static const string DICTIONARY_FILE = "dictionary.txt";

int main() {
    Lexicon dictionary(DICTIONARY_FILE);
    getLine("Press Enter to begin the game ... ");

    Boggleplay boggleplay;
    boggleplay.askForBoardGeneration(dictionary);

    while (true) {
        bool newPart = boggleplay.playOneGame();
        cout << endl;

        if (newPart){
            if (!getYesOrNo("Play again (Y/N)? ")) {
                break;
            }
            boggleplay.restore();
            boggleplay.askForBoardGeneration(dictionary);
        }
    }

    cout << "Have a nice day." << endl;
    return 0;
}
