//
//  Space.h
//  minesweeper
//
//  Created by Joshua Tumlinson on 12/1/22.
//

#ifndef Space_h
#define Space_h

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Space {
  
private:
    bool visable;
    bool flagged;
    bool containsMine;
    int numOfMines;
    
public:
    
    Space() {
        this->visable = false;
        this->flagged = false;
        this->containsMine = false;
        this->numOfMines = 0;
    }
    
    Space(bool newVisable) {
        this->visable = newVisable;
        this->flagged = false;
        this->containsMine = false;
        this->numOfMines = 0;
    }
    
    bool getVisable() {
        return this->visable;
    }
    
    bool getFlagged() {
        return this->flagged;
    }
    
    bool getContainsMines() {
        return this->containsMine;
    }
    
    int getNumOfMines() {
        return this->numOfMines;
    }
    
    void setVisable(bool newVisable) {
        this->visable = newVisable;
    }
    
    void setFlagged(bool newFlagged) {
        this->flagged = newFlagged;
    }
    
    void setContainsMines(bool newContainsMines) {
        this->containsMine = newContainsMines;
    }
    
    void setNumOfMines(int newNumOfMines) {
        this->numOfMines = newNumOfMines;
    }
};


#endif /* Space_h */
