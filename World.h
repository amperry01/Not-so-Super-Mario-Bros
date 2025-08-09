// AUTHOR INFO
// Full name: Alyssa Perry 
// Student ID: 2347996
// Chapman Email: alperry@chapman.edu 
// Course number and section: CPSC-350-02
// Assignment or exercise number: PA2: Not So Super Mario Bros

// creates a world and fills grid spaces based on input from file

#ifndef WORLD_H
#define WORLD_H 

#include <string>

using namespace std;

class World{
    public:
        World(); // default constructor
        virtual ~World(); // default destructor
        char*** worldArray; // 3D world array to show each level and its contents
        void createWorld(string inFile); // allocates memory for world array and sets every space to empty
        void fillWorld();
        void printWorld(ofstream &outFileStream);
        void printLevel(ofstream &outFileStream, int currentLevel);

        int getL(); // get num levels
        int getN(); // get NxN grid size
        int getV(); // get num lives
        
        // getters for percents
        int getCoinP();
        int getNothingP();
        int getGoombaP();
        int getKoopaP();
        int getMushroomP();
        
    private:
        int L; // number of levels
        int N; // grid dimension
        int V; // number of lives
        int coinPercent;
        int nothingPercent;
        int goombaPercent;
        int koopaPercent;
        int mushroomPercent;

        void readFile(string inFile);
        void placeObjects(int level, char object, int numOfObjects);
        void placeSingleObjectRandomly(int level, char object);
};

#endif