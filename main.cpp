// AUTHOR INFO
// Full name: Alyssa Perry 
// Student ID: 2347996
// Chapman Email: alperry@chapman.edu 
// Course number and section: CPSC-350-02
// Assignment or exercise number: PA2: Not So Super Mario Bros

#include "Gameplay.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[]){

    string inFile = argv[1];
    string outFile = argv[2];

    Gameplay game;
    game.startGame(inFile, outFile);

    return 0;
}