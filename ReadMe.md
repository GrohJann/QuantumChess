# Quantum Chess
This project aims to implement Cantwell's Quantum Chess rules based on his 2019
Paper.

## Rules
TBD

## ToDos
- GUI
  - [ ] draw checkerboard
    - [x] example implementaion can be found in src/GUI/SDL_Test.cpp
  - [ ] draw figures
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


# Requirements
- winsock (on windows)

# Licenses
The chess-pieces are licenced under [CC-BY-SA 3.0](https://creativecommons.org/licenses/by-sa/3.0/deed.en)
and authored by [Cburnett](https://commons.wikimedia.org/wiki/User:Cburnett)