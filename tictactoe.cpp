#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

// ─────────────────────────────────────────
//  STEP 1: Board Class
// ─────────────────────────────────────────
class Board {
    char grid[3][3];

public:
    Board() { reset(); }

    void reset() {
        char n = '1';
        for (auto& row : grid)
            for (auto& cell : row)
                cell = n++;
    }

    void display() const {
        cout << "\n";
        for (int r = 0; r < 3; r++) {
            cout << "  " << grid[r][0] << " | "
                         << grid[r][1] << " | "
                         << grid[r][2] << "\n";
            if (r < 2) cout << " ---+---+---\n";
        }
        cout << "\n";
    }

    // Returns true if move was valid
    bool mark(int pos, char symbol) {
        if (pos < 1 || pos > 9) return false;
        int r = (pos - 1) / 3;
        int c = (pos - 1) % 3;
        if (grid[r][c] != 'X' && grid[r][c] != 'O') {
            grid[r][c] = symbol;
            return true;
        }
        return false;
    }

    char getCell(int r, int c) const { return grid[r][c]; }
};


// ─────────────────────────────────────────
//  STEP 2: Win / Draw Detection
// ─────────────────────────────────────────
bool checkWin(const Board& b, char sym) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (b.getCell(i,0)==sym && b.getCell(i,1)==sym && b.getCell(i,2)==sym)
            return true;
        if (b.getCell(0,i)==sym && b.getCell(1,i)==sym && b.getCell(2,i)==sym)
            return true;
    }
    // Check diagonals
    if (b.getCell(0,0)==sym && b.getCell(1,1)==sym && b.getCell(2,2)==sym)
        return true;
    if (b.getCell(0,2)==sym && b.getCell(1,1)==sym && b.getCell(2,0)==sym)
        return true;
    return false;
}

bool checkDraw(const Board& b) {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (b.getCell(r,c) != 'X' && b.getCell(r,c) != 'O')
                return false;
    return true;
}


// ─────────────────────────────────────────
//  STEP 3: Minimax AI
// ─────────────────────────────────────────
int minimax(Board b, bool isMaximizing, int depth = 0) {
    if (checkWin(b, 'O')) return  10 - depth;
    if (checkWin(b, 'X')) return -10 + depth;
    if (checkDraw(b))     return 0;

    int best = isMaximizing ? -1000 : 1000;

    for (int i = 1; i <= 9; i++) {
        Board temp = b;
        if (temp.mark(i, isMaximizing ? 'O' : 'X')) {
            int score = minimax(temp, !isMaximizing, depth + 1);
            if (isMaximizing)
                best = max(best, score);
            else
                best = min(best, score);
        }
    }
    return best;
}

int bestMove(Board b) {
    int best = -1000, move = -1;
    for (int i = 1; i <= 9; i++) {
        Board temp = b;
        if (temp.mark(i, 'O')) {
            int score = minimax(temp, false);
            if (score > best) {
                best = score;
                move = i;
            }
        }
    }
    return move;
}


// ─────────────────────────────────────────
//  STEP 4: Player Input
// ─────────────────────────────────────────
int getPlayerMove() {
    int pos;
    while (true) {
        cout << "  Your move (1-9): ";
        if (cin >> pos && pos >= 1 && pos <= 9)
            return pos;
        cout << "  Invalid! Enter a number 1-9.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// ─────────────────────────────────────────
//  STEP 5: Main Game Loop
// ─────────────────────────────────────────
int main() {
    cout << "\n";
    cout << "================================\n";
    cout << "    TIC-TAC-TOE  |  vs AI      \n";
    cout << "================================\n";
    cout << "  You = X   |   AI = O\n";
    cout << "  Board positions:\n";
    cout << "   1 | 2 | 3\n";
    cout << "  ---+---+---\n";
    cout << "   4 | 5 | 6\n";
    cout << "  ---+---+---\n";
    cout << "   7 | 8 | 9\n";
    cout << "================================\n";

    char playAgain = 'y';
    int playerWins = 0, aiWins = 0, draws = 0;

    while (playAgain == 'y' || playAgain == 'Y') {
        Board board;
        bool playerTurn = true;
        bool gameOver = false;

        cout << "\n--- New Game ---\n";
        board.display();

        while (!gameOver) {
            if (playerTurn) {
                // ── Player move ──
                int move;
                while (true) {
                    move = getPlayerMove();
                    if (board.mark(move, 'X')) break;
                    cout << "  Cell already taken! Try again.\n";
                }

                board.display();

                if (checkWin(board, 'X')) {
                    cout << "  You WIN! Congratulations!\n";
                    playerWins++;
                    gameOver = true;
                } else if (checkDraw(board)) {
                    cout << "  It's a DRAW!\n";
                    draws++;
                    gameOver = true;
                }

            } else {
                // ── AI move ──
                cout << "  AI is thinking...\n";
                int move = bestMove(board);
                board.mark(move, 'O');
                cout << "  AI played position " << move << "\n";
                board.display();

                if (checkWin(board, 'O')) {
                    cout << "  AI WINS! Better luck next time.\n";
                    aiWins++;
                    gameOver = true;
                } else if (checkDraw(board)) {
                    cout << "  It's a DRAW!\n";
                    draws++;
                    gameOver = true;
                }
            }

            playerTurn = !playerTurn;
        }

        // Scoreboard
        cout << "\n================================\n";
        cout << "  SCOREBOARD\n";
        cout << "  You: " << playerWins
             << "  |  AI: " << aiWins
             << "  |  Draws: " << draws << "\n";
        cout << "================================\n";

        cout << "\n  Play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "\n  Thanks for playing! Goodbye.\n\n";
    return 0;
}
