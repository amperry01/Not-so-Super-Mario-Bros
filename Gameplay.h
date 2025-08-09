// AUTHOR INFO
// Full name: Alyssa Perry 
// Student ID: 2347996
// Chapman Email: alperry@chapman.edu 
// Course number and section: CPSC-350-02
// Assignment or exercise number: PA2: Not So Super Mario Bros

// implements actual gameplay, moving mario through each level
    // outputs a string and level grid to be added to output file at each step to log mario's interactions

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "World.h"
#include <string>

using namespace std;

class Gameplay{
    public:
        Gameplay();
        virtual ~Gameplay();
        void startGame(string inFile, string outFile);

        int m_lives;
        int m_powerLevel;
        int m_walletCoins;
        int m_marioPosRow;
        int m_marioPosCol;
        int m_gameLevel;
        bool m_fightAgain;
        int m_direction;
        int m_defeatedEnemies;
        int m_winLose;
        bool m_endGame;
        int m_lastLevel;

        void marioInit();
        void moveMario(int direction);

        void addMarioNotReplace(ofstream &outFileStream); // adds mario character to level grid without actually replacing whats there
        string getDirectionString();
        void marioInteract(ofstream &outFileStream); // marios interactions with given space on grid

        void nothingSpace();
        void eatMushroom();
        void collectCoin();
        int fightGoomba();
        int fightKoopa();
        int fightBoss();
        void warpPipe();

    private:
        World* world;
};

#endif // GAMEPLAY_H