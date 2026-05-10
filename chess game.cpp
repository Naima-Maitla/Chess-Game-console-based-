#include<iostream>
using namespace std;

#define RESET    "\033[0m"
#define BG_LIGHT "\033[48;2;240;217;181m"
#define BG_DARK  "\033[48;2;181;136;99m"
#define W_PIECE  "\033[38;2;255;255;255m"
#define B_PIECE  "\033[0;38;2;0;0;0m"

class Piece {
private:
	int row, col;
	char color, symbol;
public:
	Piece(int r, int c, char clr, char sym) {
		row = r; col = c; color = clr; symbol = sym;
	}
	int getRow() { return row; }
	int getCol() { return col; }
	char getColor() { return color; }
	char getSymbol() { return symbol; }
	void setPosition(int r, int c) { row = r; col = c; }
	virtual bool isValidMove(int toRow, int toCol, Piece* board[8][8]) = 0;
};

class Pawn : public Piece {
public:
	Pawn(int r, int c, char clr) : Piece(r, c, clr, 'P') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		if (getColor() == 'W') {
			if (toRow == getRow() - 1 && toCol == getCol()) return true;
		}
		else {
			if (toRow == getRow() + 1 && toCol == getCol()) return true;
		}
		return false;
	}
};

class Rook : public Piece {
public:
	Rook(int r, int c, char clr) : Piece(r, c, clr, 'R') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		if (toRow == getRow() || toCol == getCol()) return true;
		return false;
	}
};

class Knight : public Piece {
public:
	Knight(int r, int c, char clr) : Piece(r, c, clr, 'N') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		int rd = abs(toRow - getRow()), cd = abs(toCol - getCol());
		if ((rd == 2 && cd == 1) || (rd == 1 && cd == 2)) return true;
		return false;
	}
};

class Bishop : public Piece {
public:
	Bishop(int r, int c, char clr) : Piece(r, c, clr, 'B') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		if (abs(toRow - getRow()) == abs(toCol - getCol())) return true;
		return false;
	}
};

class Queen : public Piece {
public:
	Queen(int r, int c, char clr) : Piece(r, c, clr, 'Q') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		if ((toRow == getRow() || toCol == getCol()) ||
			(abs(toRow - getRow()) == abs(toCol - getCol()))) return true;
		return false;
	}
};

class King : public Piece {
public:
	King(int r, int c, char clr) : Piece(r, c, clr, 'G') {}
	bool isValidMove(int toRow, int toCol, Piece* board[8][8]) {
		int rd = abs(toRow - getRow()), cd = abs(toCol - getCol());
		if (rd <= 1 && cd <= 1 && !(rd == 0 && cd == 0)) return true;
		return false;
	}
};

const char* getUnicode(char sym, char color) {
	if (color == 'W') {
		if (sym == 'P') return "\xe2\x99\x99   ";
		if (sym == 'R') return "\xe2\x99\x96   ";
		if (sym == 'N') return "\xe2\x99\x98   ";
		if (sym == 'B') return "\xe2\x99\x97   ";
		if (sym == 'Q') return "\xe2\x99\x95   ";
		if (sym == 'G') return "\xe2\x99\x94   ";
	}
	else {
		if (sym == 'P') return "\xe2\x99\x9f   ";
		if (sym == 'R') return "\xe2\x99\x9c   ";
		if (sym == 'N') return "\xe2\x99\x9e   ";
		if (sym == 'B') return "\xe2\x99\x9d   ";
		if (sym == 'Q') return "\xe2\x99\x9b   ";
		if (sym == 'G') return "\xe2\x99\x9a   ";
	}
	return "    ";
}

class Board {
private:
	Piece* grid[8][8];
	bool gameOver;
public:
	Board() {
		gameOver = false;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				grid[i][j] = nullptr;

		for (int j = 0; j < 8; j++) {
			grid[6][j] = new Pawn(6, j, 'W');
			grid[1][j] = new Pawn(1, j, 'B');
		}
		grid[7][0] = new Rook(7, 0, 'W');   grid[7][7] = new Rook(7, 7, 'W');
		grid[7][1] = new Knight(7, 1, 'W'); grid[7][6] = new Knight(7, 6, 'W');
		grid[7][2] = new Bishop(7, 2, 'W'); grid[7][5] = new Bishop(7, 5, 'W');
		grid[7][3] = new Queen(7, 3, 'W');  grid[7][4] = new King(7, 4, 'W');

		grid[0][0] = new Rook(0, 0, 'B');   grid[0][7] = new Rook(0, 7, 'B');
		grid[0][1] = new Knight(0, 1, 'B'); grid[0][6] = new Knight(0, 6, 'B');
		grid[0][2] = new Bishop(0, 2, 'B'); grid[0][5] = new Bishop(0, 5, 'B');
		grid[0][3] = new Queen(0, 3, 'B');  grid[0][4] = new King(0, 4, 'B');
	}

	bool isGameOver() { return gameOver; }

	void display() {
		system("chcp 65001 > nul");
		cout << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||        CHESS GAME  -  LIVE BOARD        ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << endl;
		cout << "       a    b    c    d    e    f    g    h" << endl;
		cout << "     +----+----+----+----+----+----+----+----+" << endl;

		for (int i = 0; i < 8; i++) {
			cout << "  " << i << "  |";
			for (int j = 0; j < 8; j++) {
				bool isLight = (i + j) % 2 == 0;
				cout << (isLight ? BG_LIGHT : BG_DARK);
				if (grid[i][j] == nullptr) {
					cout << "    ";
				}
				else {
					char clr = grid[i][j]->getColor();
					char sym = grid[i][j]->getSymbol();
					if (i <= 1)
						cout << "\033[38;2;0;0;0m";        // row 0,1 = pure black
					else
						cout << "\033[38;2;255;255;255m";  // row 6,7 = pure white
					cout << getUnicode(sym, clr);
				}
				cout << RESET << "|";
			}
			cout << endl;
			cout << "     +----+----+----+----+----+----+----+----+" << endl;
		}
		cout << endl;
		cout << "  White: P=Pawn R=Rook N=Knight B=Bishop Q=Queen G=King" << endl;
	}

	void showInstructions() {
		cout << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||              HOW TO PLAY                ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  Enter row and column numbers (0 to 7)  ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  ROW GUIDE:                             ||" << endl;
		cout << "  ||  Screen row 8  =  input row 0           ||" << endl;
		cout << "  ||  Screen row 7  =  input row 1           ||" << endl;
		cout << "  ||  Screen row 6  =  input row 2           ||" << endl;
		cout << "  ||  Screen row 5  =  input row 3           ||" << endl;
		cout << "  ||  Screen row 4  =  input row 4           ||" << endl;
		cout << "  ||  Screen row 3  =  input row 5           ||" << endl;
		cout << "  ||  Screen row 2  =  input row 6           ||" << endl;
		cout << "  ||  Screen row 1  =  input row 7           ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  COL GUIDE:                             ||" << endl;
		cout << "  ||  a=0  b=1  c=2  d=3                     ||" << endl;
		cout << "  ||  e=4  f=5  g=6  h=7                     ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  EXAMPLE:                               ||" << endl;
		cout << "  ||  Move White Pawn from a2 to a3:         ||" << endl;
		cout << "  ||  From: 6 0   To: 5 0                    ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  Move Black Pawn from a7 to a6:         ||" << endl;
		cout << "  ||  From: 1 0   To: 2 0                    ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||  PIECE MOVEMENT RULES:                  ||" << endl;
		cout << "  ||  Pawn   = Forward only (1 step)         ||" << endl;
		cout << "  ||  Rook   = Straight (any distance)       ||" << endl;
		cout << "  ||  Knight = L-Shape (2+1 or 1+2)          ||" << endl;
		cout << "  ||  Bishop = Diagonal (any distance)       ||" << endl;
		cout << "  ||  Queen  = Any direction (any distance)  ||" << endl;
		cout << "  ||  King   = Any direction (1 step only)   ||" << endl;
		cout << "  ||                                         ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << endl;
	}

	bool movePiece(int r1, int c1, int r2, int c2, char currentPlayer) {
		if (grid[r1][c1] == nullptr) {
			cout << "\n  INVALID! No piece on row " << r1 << " col " << c1 << "." << endl;
			return false;
		}
		if (grid[r1][c1]->getColor() != currentPlayer) {
			cout << "\n  INVALID! That is not your piece." << endl;
			return false;
		}
		if (!grid[r1][c1]->isValidMove(r2, c2, grid)) {
			cout << "\n  INVALID MOVE! This piece cannot move there." << endl;
			return false;
		}
		if (grid[r2][c2] != nullptr && grid[r2][c2]->getColor() == currentPlayer) {
			cout << "\n  INVALID! Your own piece is already there." << endl;
			return false;
		}
		if (grid[r2][c2] != nullptr) {
			char sym = grid[r2][c2]->getSymbol();
			cout << "\n  CAPTURE! Opponent's piece captured: " << sym << endl;
			if (sym == 'G') {
				cout << "\n  ||=========================================||" << endl;
				cout << "  ||              GAME OVER!                 ||" << endl;
				cout << "  ||  " << (currentPlayer == 'W' ? "WHITE" : "BLACK");
				cout << " WINS THE GAME!                  ||" << endl;
				cout << "  ||=========================================||" << endl;
				gameOver = true;
			}
		}
		delete grid[r2][c2];
		grid[r2][c2] = grid[r1][c1];
		grid[r1][c1] = nullptr;
		grid[r2][c2]->setPosition(r2, c2);

		if (!gameOver) {
			cout << "\n  Move Successful! (" << r1 << "," << c1 << ") -> (" << r2 << "," << c2 << ")" << endl;
		}
		return true;
	}
};

class Game {
private:
	Board board;
	char currentPlayer;
public:
	Game() { currentPlayer = 'W'; }

	void showMenu() {
		cout << "\n  ||=========================================||" << endl;
		cout << "  ||               MAIN MENU                 ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << "  ||   1. Start Game                         ||" << endl;
		cout << "  ||   2. How To Play                        ||" << endl;
		cout << "  ||   3. Exit                               ||" << endl;
		cout << "  ||=========================================||" << endl;
		cout << "\n   Enter your choice: ";
	}

	void start() {
		system("cls");
		cout << "\n  ||=========================================||" << endl;
		cout << "  ||         WELCOME TO CHESS GAME!          ||" << endl;
		cout << "  ||=========================================||" << endl;

		int choice;
		showMenu();
		cin >> choice;

		if (choice == 3) { cout << "\n  Goodbye!\n"; return; }
		if (choice == 2) {
			system("cls");
			board.showInstructions();
			cout << "  Press Enter to Start Game...";
			cin.ignore(); cin.get();
		}

		while (!board.isGameOver()) {
			system("cls");
			board.display();
			cout << "\n  ||=========================================||" << endl;
			cout << "  ||  Current Player: " << (currentPlayer == 'W' ? "WHITE" : "BLACK") << "                   ||" << endl;
			cout << "  ||=========================================||" << endl;

			int r1, c1, r2, c2;
			cout << "\n  From (row col): "; cin >> r1 >> c1;
			cout << "  To   (row col): "; cin >> r2 >> c2;

			bool moved = board.movePiece(r1, c1, r2, c2, currentPlayer);

			if (moved && !board.isGameOver()) {
				currentPlayer = (currentPlayer == 'W') ? 'B' : 'W';
				cout << "\n  >>> Now it is " << (currentPlayer == 'W' ? "WHITE" : "BLACK") << "'s turn!" << endl;
				cout << "  Press Enter to continue...";
				cin.ignore(); cin.get();
			}
			else if (!moved) {
				cout << "  Press Enter to try again...";
				cin.ignore(); cin.get();
			}
		}
		system("pause");
	}
};

int main() {
	Game g;
	g.start();
	system("pause");
	return 0;
}