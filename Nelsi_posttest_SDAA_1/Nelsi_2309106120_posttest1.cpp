#include <iostream>
using namespace std;

int calculatePascalValue(int row, int col) {
    if (col == 0 || col == row) {
        return 1;
    }
    return calculatePascalValue(row - 1, col - 1) + calculatePascalValue(row - 1, col);
}

void printPascalTriangle(int levels) {
    for (int row = 0; row < levels; ++row) {
        for (int space = 0; space < (levels - row - 1); ++space) {
            cout << " ";
        }
        for (int col = 0; col <= row; ++col) {
            cout << calculatePascalValue(row, col) << " ";
        }
        cout << endl;
    }
}

int main() {
    int levels = 3; 

    cout << "Pascal's Triangle with " << levels << " levels:" << endl;
    printPascalTriangle(levels);

    return 0;
}

