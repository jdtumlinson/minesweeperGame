//
//  Board.h
//  minesweeper
//
//  Created by Joshua Tumlinson on 12/1/22.
//

#ifndef Board_h
#define Board_h

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Space.h"

using namespace std;

class Board {

private:
    int height;
    int width;
    vector<vector<Space>> board;
    bool gameOver;
    int flagsLeft;
    vector<int> mineLocations;
    
public:
    
    Board() {
        this->height = getNum("height: ");
        this->width = getNum("width: ");
        vector<vector<Space>> tempBoard(this->height, vector<Space> (this->width, false)); //create new board to copy
        this->board = tempBoard;
        this->gameOver = false;
        this->flagsLeft = 10;
    }
    
    Board(int h, int w) {
        this->height = h;
        this->width = w;
        vector<vector<Space>> tempBoard(h, vector<Space> (w, false)); //create new board to copy
        this->board = tempBoard;
        this->gameOver = false;
        this->flagsLeft = 10;
    }
    
    bool getGameOver() {
        return this->gameOver;
    }
    
    int getNum(string side) {
        int num;
        
        cout << "Enter " << side;
        cin >> num;
        cout << endl;
        
        return num;
    }
    
    void printBoard() {
        cout << "  | ";
        for(int i = 0; i < this->width; i++) cout << i + 1 << " ";
        cout << endl << "--+-";
        for(int i = 0; i < this->width; i++) cout << "--";
        cout << endl;
        
        for(int i = 0; i < this->height; i++) {
            cout << i + 1 << " | ";
            for(int j = 0; j < this->width; j++) {
                if(this->board[i][j].getFlagged() == true) cout << "F ";
                else if(this->board[i][j].getVisable() == false) cout << "- ";
                else if(this->board[i][j].getVisable() == true) {
                    if(this->board[i][j].getNumOfMines() == 0) {
                        cout << "  ";
                    }
                    else cout << this->board[i][j].getNumOfMines() << " ";
                }
            }
            cout << endl;
        }
    }
    
    void addMines() {
        for(int i = 0; i < 10; i++) {
            bool validSpot = false;
            while(validSpot == false) {
                int y = rand()%this->height;
                int x = rand()%this->width;
                if(this->board[y][x].getContainsMines() == false) {
                    this->board[y][x].setVisable(false);
                    this->board[y][x].setContainsMines(true);
                    this->mineLocations.push_back(y);
                    this->mineLocations.push_back(x);
                    validSpot = true;
                }
            }
        }
    }
    
    void addMineNumbers() {
        for(int i = 0; i < this->height; i++) { //look through every column
            for(int j = 0; j < this->width; j++) { //look through every row
                for(int k = -1; k < 2; k++) { //look between 1 below and above spot
                    for(int l = -1; l < 2; l++) { //look between 1 to the left and the right of the spot
                        if(i + k >= this->height or i + k < 0 or j + l >= this->width or j + l < 0) {
                            //do nothing
                        }
                        else {
                            if(this->board[i + k][j + l].getContainsMines() == true) {
                                this->board[i][j].setNumOfMines(this->board[i][j].getNumOfMines() + 1); //add to the mine total for that spot
                            }
                        }
                    }
                }
            }
        }
    }
    
    void guessSpace(int x, int y, string action) {
        
        if(action == "f") {
            if(flagsLeft > 0) {
                if(this->board[y][x].getVisable() == false) {
                    this->board[y][x].setFlagged(true);
                    this->flagsLeft--;
                }
                else cout << "You can't place a flag there..." << endl;
            }
            else {
                cout << "You ran out of flags..." << endl;
                gameOver = true;
            }
        }
        else {
            if(this->board[y][x].getContainsMines()) {
                this->gameOver = true;
                cout << endl << "You clicked on a mine..." << endl;
            }
                else {
                    this->board[y][x].setVisable(true);
                    setSurroundings(x, y);
                }
        }
        
    }
    
    void setSurroundings(int x, int y) {
        for(int k = -1; k < 2; k++) { //look between 1 below and above spot
            for(int l = -1; l < 2; l++) {
                if(y + k >= this->height or y + k < 0 or x + l >= this->width or x + l < 0) {
                    //do nothing
                }
                else {
                    if(board[y + k][x + l].getNumOfMines() == 0 and board[y + k][x + l].getVisable() == false) {
                        board[y + k][x + l].setVisable(true);
                        setSurroundings(x + l, y + k);
                    }
                    else if(board[y + k][x + l].getContainsMines() == false) board[y + k][x + l].setVisable(true);
                    
                }
            }
        }
    }
    
    void checkMinesStatus() {
        int minesFound = 10;
        for(int i = 0; i < 20; i += 2) {
            if(this->board[this->mineLocations[i]][this->mineLocations[i + 1]].getFlagged() == false) {
                minesFound--;
            }
        }
        if(minesFound == 10) {
            this->gameOver = true;
            cout << "You found all the mines!" << endl;
        }
    }
    
};

#endif /* Board_h */
