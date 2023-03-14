/*
KNIGHT'S TOUR USING STACK
chetan moturi CS21B017
*/
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

const int N = 8;

int chessboard[N][N];
int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
stack<pair<int, int>> stk;

bool isValidMove(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N && chessboard[x][y] == -1;
}

void printChessboard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << chessboard[i][j] << " ";
        }
        cout << endl;
    }
}

bool knightTour(int x, int y, int step) {
    chessboard[x][y] = step;
    if (step == N * N) {
        return true;
    }
    for (int i = 0; i < 8; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (isValidMove(newX, newY)) {
            stk.push({ newX, newY });
        }
    }
    while (!stk.empty()) {
        pair<int, int> curr = stk.top();
        stk.pop();
        if (knightTour(curr.first, curr.second, step + 1)) {
            return true;
        }
    }
    chessboard[x][y] = -1;
    return false;
}

int main() {
    memset(chessboard, -1, sizeof(chessboard));
    if (knightTour(0, 0, 0)) {
        printChessboard();
    }
    else {
        cout << "No solution found." << endl;
    }
    return 0;
}
