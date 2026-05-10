# Chess-Game-console-based-
Two-player console Chess Game in C++ with colored Unicode pieces, ANSI board rendering, and OOP design (inheritance, polymorphism, abstract classes).
# ♟️ Chess Game — C++ Console Application

A fully playable two-player Chess Game built in C++ featuring a
color-rendered ANSI board with Unicode chess symbols.
Demonstrates core Object-Oriented Programming principles.

## Features
- Colored board with light/dark squares using ANSI escape codes
- Unicode chess symbols (♙♖♘♗♕♔ / ♟♜♞♝♛♚)
- Two-player turn-based gameplay on an 8×8 grid
- All 6 piece types with correct movement rules
- Move validation with clear error messages
- Capture detection and King-capture win condition
- Main menu with How-to-Play instructions

## OOP Concepts
- Abstract base class `Piece` with pure virtual `isValidMove()`
- 6 derived piece classes (Pawn, Rook, Knight, Bishop, Queen, King)
- Runtime polymorphism via virtual function dispatch
- Encapsulation with private members and public getters
- `Board` class for state management, `Game` class for flow control

## Requirements
- Windows (uses `system("cls")` and `chcp 65001` for Unicode)
- Terminal with ANSI color support (Windows Terminal recommended)
- C++11 or later

## How to Run
g++ chess.cpp -o chess
./chess

## Tags
`cpp` `chess` `oop` `console-game` `ansi` `unicode` `cplusplus`
