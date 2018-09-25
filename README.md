# Boggle

## Rules of the game
The goal is to find words on the board by tracing a path through neighboring letters.
Two letters are neighbors if they adjoin each other horizontally, vertically, or diagonally.
There are up to eight letters neighboring a given cube, and each cube can be used at most once in a word.
A word is valid if it meets all of the following conditions:
 - at least 4 letters long
 - is a word found in the English dictionary
 - can be formed by connecting neighboring letter cubes (using any given cube only once)
 - has not already been formed by the player in this game (even if there are multiple paths on the board to form the same word, the word is counted at most once)
 
 To begin a game, you choose betwwen generating a random board or to manually enter a bord as a sequence of 16 characters.
 The human player plays first, entering words one by one. The score is computed according word's length (one point per letter >= 4)
 After the human has finished his turn, the computer will then find all the words that have not already been found.
 
The winner is the one with the most points

## Test
Use QT Creator to open Boggle.pro and run the source code.
