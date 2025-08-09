// AUTHOR INFO
// Full name: Alyssa Perry 
// Student ID: 2347996
// Chapman Email: alperry@chapman.edu 
// Course number and section: CPSC-350-02
// Assignment or exercise number: PA2: Not So Super Mario Bros

#include "World.h"

#include <iostream>
#include <fstream>

World::World(){
        L = 0; // number of levels
        N = 0; // grid dimension
        V = 0; // number of lives
        coinPercent = 0;
        nothingPercent = 0;
        goombaPercent = 0;
        koopaPercent = 0;
        mushroomPercent = 0;
}

World::~World(){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < N; j++){
            delete[] worldArray[i][j]; // delete each row in a level
        }
        delete[] worldArray[i]; // delete each level
    }
    delete[] worldArray; // delete array of levels
}

void World::createWorld(string inFile){

    readFile(inFile);

    worldArray = new char**[L]; // allocates memory for levels
    for(int i = 0; i < L; i++){
        worldArray[i] = new char*[N]; // allocates memory for rows in each level
        for(int j = 0; j < N; j++){
            worldArray[i][j] = new char[N]; // allocates memory for columns in each row
            for(int k = 0; k < N; k++){
                worldArray[i][j][k] = 'x'; // sets every space in world grid to empty
            }
        }
    }

    fillWorld();
}

void World::fillWorld(){
    srand(time(NULL));
    int tilesInEachLevel = N * N;
    for(int i = 0; i < L; i++){ // go through each level 
        placeObjects(i, 'c', (tilesInEachLevel * coinPercent) / 100); // % of coins placed
        placeObjects(i, 'x', (tilesInEachLevel * nothingPercent) / 100); // ensures percent of nothing
        placeObjects(i, 'g', (tilesInEachLevel * goombaPercent) / 100); // % of goombas placed
        placeObjects(i, 'k', (tilesInEachLevel * koopaPercent) / 100); // % of koopas placed
        placeObjects(i, 'm', (tilesInEachLevel * mushroomPercent) / 100); // % of mushrooms placed
        placeSingleObjectRandomly(i, 'b'); // place boss randomly

        if(i != L - 1){ // places warp pipes except in last level
            placeSingleObjectRandomly(i, 'w');
        }
    }
}

void World::placeObjects(int level, char object, int numOfObjects){
    for(int i = 0; i < numOfObjects; i++){
        placeSingleObjectRandomly(level, object);
    }
}

void World::placeSingleObjectRandomly(int level, char object){
    int row;
    int col;
    do{ // do-while instead of normal while because I need to set row and column before beginning to check for 'x'
        row = rand() % N; // random row index
        col = rand() % N; // random col index
    } while(worldArray[level][row][col] != 'x');
    worldArray[level][row][col] = object; // place object when tile is empty 
}

// prints entire world for debugging
void World::printWorld(ofstream &outFileStream){
    // ofstream outFile(output);
    // outFile.open(output); // redundant open() causing code to not write to log file at all

    for(int i = 0; i < L; i++){
        // cout << "Level: " << i << endl;
        outFileStream << "Level: " << i << endl;
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // cout << worldArray[i][j][k] << " ";
                outFileStream << worldArray[i][j][k] << " "; // print each position of the grid
            }
            // cout << endl;
            outFileStream << endl;
        }
        outFileStream << endl;
    }
}

void World::printLevel(ofstream &outFileStream, int currentLevel){
    // outFileStream << "Level: " << currentLevel << endl;
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            outFileStream << worldArray[currentLevel][j][k] << " "; // print each position of the grid
        }
        outFileStream << endl;
    }
}

void World::readFile(string input){
    ifstream inFile(input);
    string line;

    getline(inFile, line);
    L = stoi(line);
    getline(inFile, line);
    N = stoi(line);
    getline(inFile, line);
    V = stoi(line);
    getline(inFile, line);
    coinPercent = stoi(line);
    getline(inFile, line);
    nothingPercent = stoi(line);
    getline(inFile, line);
    goombaPercent = stoi(line);
    getline(inFile, line);
    koopaPercent = stoi(line);
    getline(inFile, line);
    mushroomPercent = stoi(line);

    inFile.close();
}

int World::getL(){
    return L;
}

int World::getN(){
    return N;
}

int World::getV(){
    return V;
}

int World::getCoinP(){
    return coinPercent;
}

int World::getNothingP(){
    return nothingPercent;
}

int World::getGoombaP(){
    return goombaPercent;
}

int World::getKoopaP(){
    return koopaPercent;
}

int World::getMushroomP(){
    return mushroomPercent;
}
