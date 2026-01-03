# Quantum Chess
This project aims to implement Cantwell's Quantum Chess rules based on his 2019
Paper.

## Rules
TBD

## ToDos
- GUI
  - [x] draw checkerboard
    - [x] example implementaion can be found in src/GUI/SDL_Test.cpp
  - [x] draw figures
  - [ ] be able to display quantum state of figure
  - [ ] add startup window to choose whether to start a client or server
- Networking
  - [ ] develop protocol for communication between server and client
  - [ ] implement client protocol
    - [ ] for windows
    - [ ] for linux
  - [ ] implement server protocol
    - [ ] for windows
    - [ ] for linux
  - [ ] write protocol explanation
- Logic
  - [ ] add all normal chess moves
    - [ ] Pawn
    - [ ] Rook
    - [ ] Knight
    - [ ] Bishop
    - [ ] Queen
    - [ ] King
  - [ ] add quantum chess moves
    - [ ] split
    - [ ] merge

## Requirements
- winsock (on windows)

## TODOs
### GameLogic
click on figure -> check if players turn -> get possible moves
-> render possible moves on chess board -> deselect figure if first figure was selected again, otherwise move figure -> change turn

make it work for quantum moves


## Assets and Attribution
### Chess Pieces
- **JohnPablok's improved Cburnett chess set** <br>
  Source: https://opengameart.org/content/chess-pieces-and-board-squares <br>
  License: [CC-BY-SA 3.0](https://creativecommons.org/licenses/by-sa/3.0/)

### Move Icons
- **Split Icon** by iconbysonny <br>
  Source: https://thenounproject.com/icon/split-5133847/ <br>
  License: [CC-BY 3.0](https://creativecommons.org/licenses/by/3.0/)
- **Merge Icon** by iconbysonny <br>
  Source: https://thenounproject.com/icon/merger-5133844/ <br>
  License: [CC-BY 3.0](https://creativecommons.org/licenses/by/3.0/)
- **Arrow Icon** by iconbysonny <br>
  Source: https://thenounproject.com/icon/up-arrow-5133890/ <br>
  License: [CC-BY 3.0](https://creativecommons.org/licenses/by/3.0/)



# License
This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

