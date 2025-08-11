# Not so Super Mario Bros.

A C++ text-based adventure game where Mario navigates through multiple worlds, collects coins, gains power-ups, and battles bosses — all in the terminal.  
Originally developed for Chapman University's CPSC 350: Data Structures course, this project demonstrates **object-oriented design**, **game logic**, and **file I/O** in C++.

---

## Features
- Multi-level gameplay with increasing difficulty
- Coin collection and wallet tracking
- Power-up system to boost player stats
- Boss battles with varying difficulty
- Player health, score tracking, and win/loss conditions
- Modular architecture for maintainability

---

## Tech Stack
- **Language:** C++
- **Paradigms:** Object-Oriented Programming (OOP)
- **Data Handling:** File I/O for input parsing and gameplay logging

---

## Sample Gameplay Output
```text
Level: 0
g m b c
x c k c
m k x k
g w m c

Current level: 0 | Mario position: 1,1 | Mario power level: 0
Mario collected a coin.
Mario Lives: 3 | Coins in wallet: 1 | Next move: DOWN

...

Current level: 0 | Mario position: 2,2 | Mario power level: 0
Mario fought a Koopa and lost.
Mario Lives: 2 | Coins in wallet: 1 | Next move: STAY PUT
```

---

## How to Run
- Clone repo: git clone https://github.com/amperry01/Not-so-Super-Mario-Bros.git
- Compile code: g++ *.cpp -o mario
- Run game: ./mario input.txt log.txt
