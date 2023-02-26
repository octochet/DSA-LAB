#include <iostream>
using namespace std;

// Dimension of square chessboard
// Value of N has to be in range [5,71]
const int N = 8;

// chessboard 
int chessboard[N][N];

// dx and dy arrays for legal moves of a knight
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// function to check if a move is legal
bool isLegal(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && chessboard[x][y] == -1);
}

// function to find the next move using Warnsdorff's algorithm
// x = current x location
// y = current y location
// moveCount  = number of mves done until now
bool findNextMove(int x, int y, int moveCount) {
    // base case: all squares have been visited
    if (moveCount == N * N) {
        return true;
    }

    int minMoves = 9;
    int minX, minY;
    for (int i = 0; i < 8; i++) {
        int nextX = x + dx[i];
        int nextY = y + dy[i];
        if (isLegal(nextX, nextY)) {
            int moves = 0;
            for (int j = 0; j < 8; j++) {
                int x1 = nextX + dx[j];
                int y1 = nextY + dy[j];
                if (isLegal(x1, y1)) {
                    moves++;
                }
            }
            if (moves < minMoves) {
                minMoves = moves;
                minX = nextX;
                minY = nextY;
            }
        }
    }

    // if a move is found, mark the square as visited and move to it
    if (minMoves < 9) {
        chessboard[minX][minY] = moveCount;
        if (findNextMove(minX, minY, moveCount + 1)) {
            return true;
        } else {
            chessboard[minX][minY] = -1;
        }
    }

    // backtrack if no move is found
    return false;
}

int main() {
    // initialize chessboard
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            chessboard[i][j] = -1;
        }
    }

    // initialize start to 0 and mark it visited
    int startX = 0, startY = 0;
    chessboard[startX][startY] = 0;

    // solve 
    if (findNextMove(startX, startY, 1)) {
        // print the solution
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << chessboard[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
