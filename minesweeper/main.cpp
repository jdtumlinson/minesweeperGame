//
//  main.cpp
//  minesweeper
//
//  Created by Joshua Tumlinson on 12/1/22.
//

#include <iostream>
#include <string>
#include <vector>
#include "Board.h"

using namespace std;

void getUserInput(int &x, int &y, string &action) {
    cout << "Enter an x value: ";
    cin >> x;
    x--;
    cout << "Enter a y value: ";
    cin >> y;
    y--;
    cout << "Enter an action ('f' to flag or 'c' to click): ";
    cin >> action;
    cout << endl;
}

int main() {
    srand(time(NULL));
    
    int guessX = 0;
    int guessY = 0;
    string userAction = "";
        
    Board newBoard;
    newBoard.addMines();
    newBoard.addMineNumbers();
    newBoard.printBoard();
    while(newBoard.getGameOver() == false) {
        getUserInput(guessX, guessY, userAction);
        newBoard.guessSpace(guessX, guessY, userAction);
        if(newBoard.getGameOver() != false) {
            newBoard.printBoard();
            newBoard.checkMinesStatus();
        }
    }
    
    return 0;
}
