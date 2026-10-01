// EECS 348 Lab 5 - Matrix Operations
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

using Matrix = vector<vector<int>>;

// Print a matrix with right-aligned columns sized to the widest value.
void printMatrix(const Matrix& m) {
    size_t width = 1;
    for (const auto& row : m)
        for (int v : row)
            width = max(width, to_string(v).size());
    for (const auto& row : m) {
        for (int v : row)
            cout << setw(static_cast<int>(width) + 2) << v;
        cout << '\n';
    }
}

// 1. Load N and two NxN matrices from a file. Returns false on failure.
bool loadMatrices(const string& filename, int& n, Matrix& a, Matrix& b) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error: could not open file '" << filename << "'\n";
        return false;
    }
    if (!(in >> n) || n <= 0) {
        cerr << "Error: first line must be a positive integer N\n";
        return false;
    }
    a.assign(n, vector<int>(n));
    b.assign(n, vector<int>(n));
    for (Matrix* m : {&a, &b})
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (!(in >> (*m)[i][j])) {
                    cerr << "Error: file does not contain enough values\n";
                    return false;
                }
    return true;
}

// 2. Add two matrices.
Matrix addMatrices(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix c(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
    return c;
}

// 3. Multiply two matrices.
Matrix multiplyMatrices(const Matrix& a, const Matrix& b) {
    int n = a.size();
    Matrix c(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

// 4. Sums of the main and secondary diagonals.
void diagonalSums(const Matrix& m) {
    int n = m.size();
    int mainSum = 0, secondarySum = 0;
    for (int i = 0; i < n; i++) {
        mainSum += m[i][i];
        secondarySum += m[i][n - 1 - i];
    }
    cout << "Main diagonal sum: " << mainSum << '\n';
    cout << "Secondary diagonal sum: " << secondarySum << '\n';
}

// 5. Swap two rows (takes a copy so the original is untouched).
void swapRows(Matrix m, int r1, int r2) {
    int n = m.size();
    if (r1 < 0 || r1 >= n || r2 < 0 || r2 >= n) {
        cout << "Error: row index out of bounds\n";
        return;
    }
    swap(m[r1], m[r2]);
    printMatrix(m);
}

// 6. Swap two columns.
void swapCols(Matrix m, int c1, int c2) {
    int n = m.size();
    if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) {
        cout << "Error: column index out of bounds\n";
        return;
    }
    for (int i = 0; i < n; i++)
        swap(m[i][c1], m[i][c2]);
    printMatrix(m);
}

// 7. Update a single element.
void updateElement(Matrix m, int r, int c, int value) {
    int n = m.size();
    if (r < 0 || r >= n || c < 0 || c >= n) {
        cout << "Error: row or column index out of bounds\n";
        return;
    }
    m[r][c] = value;
    printMatrix(m);
}

int main() {
    string filename;
    cout << "Enter input file name: ";
    cin >> filename;

    int n;
    Matrix a, b;
    if (!loadMatrices(filename, n, a, b))
        return 1;

    cout << "\nMatrix A:\n";
    printMatrix(a);
    cout << "\nMatrix B:\n";
    printMatrix(b);

    cout << "\nA + B:\n";
    printMatrix(addMatrices(a, b));

    cout << "\nA * B:\n";
    printMatrix(multiplyMatrices(a, b));

    cout << "\nDiagonal sums of A:\n";
    diagonalSums(a);

    int i, j, v;
    cout << "\nEnter two row indices to swap in A: ";
    cin >> i >> j;
    swapRows(a, i, j);

    cout << "\nEnter two column indices to swap in A: ";
    cin >> i >> j;
    swapCols(a, i, j);

    cout << "\nEnter row, column, and new value to update in A: ";
    cin >> i >> j >> v;
    updateElement(a, i, j, v);

    return 0;
}
