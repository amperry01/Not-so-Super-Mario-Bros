// AUTHOR INFO
// Full name: Alyssa Perry 
// Student ID: 2347996
// Chapman Email: alperry@chapman.edu 
// Course number and section: CPSC-350-02
// Assignment or exercise number: PA2: Not So Super Mario Bros

#include "Gameplay.h"

#include <iostream>
#include <fstream>


Gameplay::Gameplay(){
    world = new World();
    m_lives = 0;
    m_powerLevel = 0;
    m_walletCoins = 0;
    m_gameLevel = 0;
    m_marioPosRow = -1;
    m_marioPosCol = -1;
    m_fightAgain = false;
    m_direction = -2;
    m_defeatedEnemies = 0;
    m_winLose = -1; // 1 win, 0 lose
    m_endGame = false; // false keep playing, true end game
    m_lastLevel = -1;
}

Gameplay::~Gameplay(){
    if(world != NULL){
       delete world;
    }
}

void Gameplay::startGame(string inFile, string outFile){
    world->createWorld(inFile);
    ofstream outFileStream(outFile, ios::trunc); // opens and clears file for fresh log if it already existed before starting game
    outFileStream.close();
    outFileStream.open(outFile, ios::app); // opening file in append mode to be able to add to it in World.cpp
    world->printWorld(outFileStream);

    m_lastLevel = world->getL() - 1;
    
    // initialize mario lives and starting position
    marioInit();

    // gameplay starts here
    while(m_endGame == false){
        outFileStream << "Current level: " << m_gameLevel << " | Mario position: " << m_marioPosRow << "," << m_marioPosCol 
            << " | Mario power level: " << m_powerLevel << endl;

        marioInteract(outFileStream);

        if(m_defeatedEnemies == 7){
            m_lives++;
            m_defeatedEnemies = 0;
        }
        
        if(m_fightAgain == true){
            m_fightAgain = false;
            outFileStream << "Mario lives: " << m_lives << " | Coins in wallet: " << m_walletCoins << " | Next move: STAY PUT" << endl;

            if(m_endGame == true){
                break;
            }

            addMarioNotReplace(outFileStream);           

        } else {
            m_direction = rand() % 4; // random direction with 4 choices
            outFileStream << "Mario lives: " << m_lives << " | Coins in wallet: " << m_walletCoins << " | Next move: " << getDirectionString() << endl;
            
            if(m_endGame == true){
                break;
            }

            addMarioNotReplace(outFileStream);
            moveMario(m_direction);
        }

        outFileStream << endl;
    }

    if(m_endGame == true){
        outFileStream.close();
    }
}

void Gameplay::marioInit(){
    // initialize mario lives and starting position
    m_lives = world->getV();
    srand(time(NULL));
    m_marioPosRow = rand() % world->getN();
    m_marioPosCol = rand() % world->getN();
}

void Gameplay::moveMario(int direction){
    if(world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] == 'H' && m_direction != -1){ // if mario didn't lose to enemy and moved on (replacing enemy char on grid)
        world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'x'; // replace last postion with empty to show mario moving away
    }

    switch(direction){
        case 0: // MOVE UP
            if(m_marioPosRow > 0){
                m_marioPosRow--;
            } else {
                m_marioPosRow = world->getN() - 1; // wrap around grid and avoid out of bounds
            }
            break;
        case 1: // MOVE DOWN
            if(m_marioPosRow < world->getN() - 1){
                m_marioPosRow++;
            } else {
                m_marioPosRow = 0; // wrap around grid and avoid out of bounds
            }
            break;
        case 2: // MOVE LEFT
            if(m_marioPosCol > 0){
                m_marioPosCol--;
            } else {
                m_marioPosCol = world->getN() - 1; // wrap around grid and avoid out of bounds
            }
            break;
        case 3: // MOVE RIGHT
            if(m_marioPosCol < world->getN() - 1){
                m_marioPosCol++;
            } else {
                m_marioPosCol = 0; // wrap around grid and avoid out of bounds
            }
            break;
    }
}

// adds mario character to level grid without actually replacing whats there
void Gameplay::addMarioNotReplace(ofstream &outFileStream){
    if(world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] != 'H'){
        char temp = world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol];
        world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'H';
        // print character array with mario current position where the last interaction took place before moving to next position
        world->printLevel(outFileStream, m_gameLevel);
        world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = temp;
    } else {
        world->printLevel(outFileStream, m_gameLevel);
    }
}

string Gameplay::getDirectionString(){
    string directionStr = "";
    if(m_direction == 0){
        directionStr = "UP";
    } else if(m_direction == 1){
        directionStr = "DOWN";
    } else if(m_direction == 2){
        directionStr = "LEFT";
    } else if(m_direction == 3){
        directionStr = "RIGHT";
    }

    return directionStr;
}

// Interactions

// marios interactions with given space on grid
void Gameplay::marioInteract(ofstream &outFileStream){
    // output action taken while completing interactions
        switch(world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol]){
            case 'x':
                nothingSpace();
                outFileStream << "The position is empty." << endl;
                break;
            case 'm':
                eatMushroom();
                outFileStream << "Mario ate a mushroom." << endl;
                break;
            case 'c':
                collectCoin();
                outFileStream << "Mario collected a coin." << endl;
                break;
            case 'g':
                m_winLose = fightGoomba();
                if(m_winLose == 0){
                    outFileStream << "Mario fought a Goomba and lost." << endl;
                    m_defeatedEnemies = 0;
                    if(m_lives < 1){
                        outFileStream << "Mario died, the game is lost." << endl;
                        // end game
                        m_endGame = true;
                    } 
                } else if(m_winLose == 1){
                    outFileStream << "Mario fought a Goomba and won." << endl;
                    m_defeatedEnemies++;
                }
                break;
            case 'k':
                m_winLose = fightKoopa();
                if(m_winLose == 0){
                    outFileStream << "Mario fought a Koopa and lost." << endl;
                    m_defeatedEnemies = 0;
                    if(m_lives < 1){
                        outFileStream << "Mario died, the game is lost." << endl;
                        // end game
                        m_endGame = true;
                    } 
                } else if(m_winLose == 1){
                    outFileStream << "Mario fought a Koopa and won." << endl;
                    m_defeatedEnemies++;
                }
                break;
            case 'b':
                m_winLose = fightBoss();
                if(m_winLose == 0){
                    outFileStream << "Mario fought the level boss and lost." << endl;
                    m_defeatedEnemies = 0;
                    if(m_lives < 1){
                        outFileStream << "Mario died, the game is lost." << endl;
                        // end game
                        m_endGame = true;
                    }
                } else if(m_winLose == 1){
                    outFileStream << "Mario fought the level boss and won." << endl;
                    m_defeatedEnemies++;

                    if(m_endGame == true){
                        outFileStream << "Mario saved the princess, the game is won!" << endl;
                    }
                }
                break;
            case 'w':
                warpPipe();
                outFileStream << "Mario warped." << endl;
                break;
        }
} 

void Gameplay::nothingSpace(){
    world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'H';
}

void Gameplay::collectCoin(){
    m_walletCoins++;
    if(m_walletCoins == 20){
        m_lives++;
        m_walletCoins = 0;
    }
    world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'H';
}

void Gameplay::eatMushroom(){
    if(m_powerLevel < 2){
        m_powerLevel++;
    }
    world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'H';
}

int Gameplay::fightGoomba(){
    int probability = rand() % 100;
    int ret = -1;
    if(probability < 80){
        ret = 1; // 1 for win
        world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'H';
    } else {
        ret = 0; // 0 for lose
        if(m_powerLevel > 0){ // lose with PL1 or PL2
            m_powerLevel--; // decrease power level by one
            world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'g'; // goomba stays in position
            m_fightAgain = false; // mario moves on
        } else { // lose with PL0
            m_lives--; // lose life
            m_powerLevel = 0;
            m_fightAgain = true; // fight again... if game does not end
        }
    }
    return ret;
}

int Gameplay::fightKoopa(){
    int probability = rand() % 100;
    int ret = -1;
    if(probability < 65){
        ret = 1; // 1 for win
        world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'H';
    } else {
        ret = 0; // 0 for lose
        if(m_powerLevel > 0){ // lose with PL1 or PL2
            m_powerLevel--; // decrease power level by one
            world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'k'; // koopa troopa stays in position
            m_fightAgain = false; // mario moves on
        } else { // lose with PL0
            m_lives--; // lose life
            m_powerLevel = 0;
            m_fightAgain = true; // fight again... if game does not end
        }
    }
    return ret;
}

int Gameplay::fightBoss(){
    int probability = rand() % 100;
    int ret = -1;
    if(probability < 50){
        ret = 1; // 1 for win
        if(m_gameLevel < m_lastLevel){
            m_gameLevel++;
        } else {
            m_endGame = true;
        }
        m_marioPosRow = rand() % world->getN();
        m_marioPosCol = rand() % world->getN();
    } else {
        ret = 0; // 0 for lose
        if(m_powerLevel > 1){ // lose with PL2
            m_powerLevel -= 2; // decrease power level by two
            world->worldArray[m_gameLevel][m_marioPosRow][m_marioPosCol] = 'b'; // boss stays in position
            m_fightAgain = true; // mario fights again
        } else { // lose with PL0 or PL1
            m_lives--; // lose life
            m_powerLevel = 0;
            m_fightAgain = true; // fight again... if game does not end
        }
    }
    return ret;
}

void Gameplay::warpPipe(){
    m_gameLevel++;
    m_marioPosRow = rand() % world->getN();
    m_marioPosCol = rand() % world->getN();
}
