// AUTHOR INFO
// Full name: Alyssa Perry 
// Student ID: 2347996
// Chapman Email: alperry@chapman.edu 
// Course number and section: CPSC-350-02
// Assignment or exercise number: PA2: Not So Super Mario Bros

OVERVIEW
A C++ program a Not So Super Mario Bros. simulation carried out in a world that consists of a fixed number of levels. 
Mario must navigate the levels, encountering enemies and power ups, and collecting coins, before engaging a boss to move onto the next level.
These actions continue until Mario beats the Boss in the last level and saves the princess, or loses all of his lives, which also ends the game.

SOURCE FILES
main.cpp
World.cpp /World.h
Gameplay.cpp /Gameplay.h

input.txt
log.txt

ERRORS
There are no known complie or runtime errors.

REFERENCES
- https://www.w3schools.com/cpp/cpp_do_while_loop.asp
- https://stackoverflow.com/questions/7748071/same-random-numbers-every-time-i-run-the-program
- "how to add to the same file from different classes c++" in chatgpt to get an example for writing 
    to the same file from different classes using append mode "ios::app" 
    ** only used "ios::app" from example, mainly just used it to understand how to implement this logic
- https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c#:~:text=If%20you%20simply%20open%20the,you'll%20delete%20the%20content. 
    used to learn how to clear a file before adding to it using "ios::trunc"
- https://www.sololearn.com/en/Discuss/2848548/what-is-the-difference-between-iosout-or-iostrunc 
    used to better understand what "ios::trunc" was doing

RUN INSTRUCTIONS
To compile: g++ *.cpp -o A2.exe
To run: ./A2.exe input.txt log.txt





