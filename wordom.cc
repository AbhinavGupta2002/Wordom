// WORDOM - Developed by Abhinav Gupta

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <utility>
#include "Escape_Sequences_Colors.h"
using namespace std;
vector<string> dictionary;
int dictionary_size;

// c is a letter in word
bool isYellow(char c, string word) {
    for (int i = 0; i < 5; ++i) {
        if (c == word[i]) {
            return true;
        }
    }
    return false;
}

// blocks a letter in word
void blockLetter(string& word, char c) {
    for (int i = 0; i < 5; ++i) {
        if (word[i] == c) {
            word[i] = '-';
            break;
        }
    }
}

// sets the color of the letter
void setLetter(string guess, string& word, int position) {
    if (isYellow(guess[position], word) == true) {
        if (word[position] == guess[position]) {
            cout << COLOR_GREEN_NORMAL;
        } else {
            cout << COLOR_YELLOW_NORMAL;
        }
        blockLetter(word, guess[position]);
    } else {
        cout << COLOR_RED_NORMAL;
    }
}

// prints the entire wordom board
void printBoard(vector<string> attempts, string word) {
    cout << COLOR_BOLD;
    cout << "---------------------" << endl;
    for (int i = 0; i < 6; ++i) {
        string temp_word = word;
        if (i >= attempts.size() || attempts[i].size() == 0) {
            cout << "|   |   |   |   |   |";
        } else {
            cout << "| ";
            setLetter(attempts[i], temp_word, 0);
            cout << attempts[i][0];
            cout << COLOR_NORMAL << COLOR_BOLD;
            cout << " | ";
            setLetter(attempts[i], temp_word, 1);
            cout << attempts[i][1];
            cout << COLOR_NORMAL << COLOR_BOLD;
            cout << " | ";
            setLetter(attempts[i], temp_word, 2);
            cout << attempts[i][2];
            cout << COLOR_NORMAL << COLOR_BOLD;
            cout << " | ";
            setLetter(attempts[i], temp_word, 3);
            cout << attempts[i][3];
            cout << COLOR_NORMAL << COLOR_BOLD;
            cout << " | ";
            setLetter(attempts[i], temp_word, 4);
            cout << attempts[i][4];
            cout << COLOR_NORMAL << COLOR_BOLD;
            cout << " |";
        }
        cout << endl << "---------------------" << endl;
    }
    cout << COLOR_NORMAL;
}

// prints the title
void printIntro() {
    cout << COLOR_BOLD;
    cout << COLOR_GREEN_NORMAL << "--" << COLOR_YELLOW_NORMAL << "--" << COLOR_RED_NORMAL << "--";
    cout << COLOR_WHITE_MAGENTA << COLOR_BOLD << " WORDOM ";
    cout << COLOR_RED_NORMAL << "--" << COLOR_YELLOW_NORMAL << "--" << COLOR_GREEN_NORMAL << "--" << endl << endl << endl;
    cout << COLOR_NORMAL;
}

// resets the game board
void resetGame(vector<string>& attempts) {
    attempts.clear();
    cout << COLOR_NORMAL;
    cout << endl << endl << endl << endl << endl;
}

// dictionary must be set before calling this
bool isWord(std::string word) {
    for (int i = 0; i < dictionary_size; ++i) {
        if (word == dictionary[i]) {
            return true;
        }
    }
    return false;
}

// checks if user-made guess is a valid entry
std::pair<bool, std::string> validGuess(string word) {
    if (word.size() != 5) {
        return std::make_pair(false, "Input Must Be 5 Letters. Try Again!");
    }
    for (int i = 0; i < 5; ++i) {
        int ascii_value = (int)word[i];
        if (ascii_value < 65 || ascii_value > 90) {
            return std::make_pair(false, "Invalid Input. Try Again!");
        }
    }
    return std::make_pair(isWord(word), "Input Is Not A Word In The Dictionary. Try Again!");
}

// sets the dictionary of 5-letter words that are in uppercase letters
void setDictionary() {
    ifstream file("dict1.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.size() == 6) {
                line = line.substr(0, 5);
                dictionary.push_back(line);
            }
        }
        file.close();
    }
    dictionary_size = dictionary.size();
}

// clears the screen
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int main() {
    setDictionary();
    srand (time(NULL));
    vector<string> attempts;
    while (true) {
        bool playAgain = false;
        bool winner = false;
        int index = rand() % dictionary_size + 1;
        --index;
        string word = dictionary[index]; // a 5-letter word is chosen randomly from dictionary
        int i = 1;
        clearScreen();
        printIntro();
        printBoard(attempts, word);
        std::cout << endl;
        while (i <= 6) {
            string guess;
            cout << "Attempt " << i << ": ";
            cin >> guess;
            std::pair <bool, std::string> decision = validGuess(guess);
            if (decision.first == false) {
                cout << decision.second << endl;
                continue;
            }
            cout << endl;
            attempts.push_back(guess);
            clearScreen();
            printIntro();
            printBoard(attempts, word);
            cout << endl;
            if (attempts[attempts.size() - 1] == word) {
                winner = true;
                break;
            }
            ++i;
        }
        cout << COLOR_BOLD << endl << endl;
        if (winner == true) {
            cout << COLOR_GREEN_NORMAL << "You Won!" << endl;
        } else {
            cout << COLOR_RED_NORMAL << "You Lost!" << endl << endl;
            cout << COLOR_NORMAL << COLOR_BOLD << "The Answer Was " << COLOR_MAGENTA_NORMAL << word << endl;
        }
        cout << COLOR_NORMAL << endl << endl;
        while(true) {
            string input;
            cout << "Would You Like To Play Again? (yes/no)" << endl;
            cin >> input;
            if (input == "yes") {
                playAgain = true;
                break;
            } else if (input == "no") {
                break;
            }
            cout << "Invalid Input. Try Again!" << endl;
        }
        if (playAgain == false) {
            break;
        }
        resetGame(attempts);
    }
}
