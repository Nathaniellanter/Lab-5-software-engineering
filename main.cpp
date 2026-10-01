// EECS 348 Lab 5 - Matrix Operations
// Only <iostream> and <fstream> are used, so matrices are stored as
// dynamically allocated 2D arrays (int**) instead of std::vector.
#include <iostream>
#include <fstream>

using namespace std;

// ---------- Memory helpers ----------

// Allocate an n x n matrix, with every element initialized to 0.
int** createMatrix(int n) {
    int** m = new int*[n];            // array of row pointers
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];            // each row holds n ints
        for (int j = 0; j < n; j++)
            m[i][j] = 0;
    }
    return m;
}

// Free all memory used by an n x n matrix.
void freeMatrix(int** m, int n) {
    for (int i = 0; i < n; i++)
        delete[] m[i];                // free each row
    delete[] m;                       // free the row-pointer array
}

// Make an independent copy of an n x n matrix, so operations that
// modify a matrix don't change the original.
int** copyMatrix(int** m, int n) {
    int** c = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = m[i][j];
    return c;
}

// ---------- Output helpers ----------

// Count how many characters a number takes up when printed (including '-').
int numLength(int v) {
    int len = (v < 0) ? 1 : 0;        // room for the minus sign
    if (v < 0) v = -v;
    if (v == 0) return 1;
    while (v > 0) {                   // one character per digit
        len++;
        v /= 10;
    }
    return len;
}

// Print a number right-aligned in a field of the given width
// (this replaces setw from <iomanip>).
void printPadded(int v, int width) {
    for (int s = numLength(v); s < width; s++)
        cout << ' ';
    cout << v;
}

// Print a matrix with aligned columns. The column width is at least 4
// and grows if the matrix contains wider numbers.
void printMatrix(int** m, int n) {
    int width = 4;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (numLength(m[i][j]) + 1 > width)
                width = numLength(m[i][j]) + 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printPadded(m[i][j], width);
        cout << endl;
    }
}

// ---------- Problem 1: read matrices from a file ----------

// Reads N, then matrix A, then matrix B from the file.
// Returns false (and leaves a=b=nullptr) if anything goes wrong.
bool loadMatrices(const char* filename, int& n, int**& a, int**& b) {
    a = nullptr;
    b = nullptr;

    ifstream in(filename);
    if (!in) {
        cerr << "Error: could not open file " << filename << endl;
        return false;
    }
    if (!(in >> n) || n <= 0) {       // N must be a positive integer
        cerr << "Error: first value must be a positive integer N" << endl;
        return false;
    }

    a = createMatrix(n);
    b = createMatrix(n);

    // Read the n*n values of A, then the n*n values of B.
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(in >> a[i][j])) {
                cerr << "Error: not enough values in file" << endl;
                freeMatrix(a, n);
                freeMatrix(b, n);
                a = b = nullptr;
                return false;
            }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (!(in >> b[i][j])) {
                cerr << "Error: not enough values in file" << endl;
                freeMatrix(a, n);
                freeMatrix(b, n);
                a = b = nullptr;
                return false;
            }
    return true;
}

// ---------- Problem 2: add two matrices ----------

// Prints a + b (element-by-element sum).
void addMatrices(int** a, int** b, int n) {
    int** c = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
    printMatrix(c, n);
    freeMatrix(c, n);
}

// ---------- Problem 3: multiply two matrices ----------

// Prints a * b. Element (i,j) is the dot product of row i of a
// with column j of b.
void multiplyMatrices(int** a, int** b, int n) {
    int** c = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
    printMatrix(c, n);
    freeMatrix(c, n);
}

// ---------- Problem 4: diagonal sums ----------

// Prints the sum of the main diagonal (top-left to bottom-right) and
// the secondary diagonal (top-right to bottom-left).
void diagonalSums(int** m, int n) {
    int mainSum = 0;
    int secondarySum = 0;
    for (int i = 0; i < n; i++) {
        mainSum += m[i][i];               // elements (0,0), (1,1), ...
        secondarySum += m[i][n - 1 - i];  // elements (0,n-1), (1,n-2), ...
    }
    cout << "Main diagonal sum: " << mainSum << endl;
    cout << "Secondary diagonal sum: " << secondarySum << endl;
}

// ---------- Problem 5: swap rows ----------

// Swaps rows r1 and r2 (0-indexed) of a copy of m and prints it.
// Prints an error instead if either index is out of bounds.
void swapRows(int** m, int n, int r1, int r2) {
    if (r1 < 0 || r1 >= n || r2 < 0 || r2 >= n) {
        cout << "Error: row index out of bounds" << endl;
        return;
    }
    int** c = copyMatrix(m, n);
    int* temp = c[r1];                // swapping row pointers swaps whole rows
    c[r1] = c[r2];
    c[r2] = temp;
    printMatrix(c, n);
    freeMatrix(c, n);
}

// ---------- Problem 6: swap columns ----------

// Swaps columns c1 and c2 (0-indexed) of a copy of m and prints it.
// Prints an error instead if either index is out of bounds.
void swapColumns(int** m, int n, int c1, int c2) {
    if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) {
        cout << "Error: column index out of bounds" << endl;
        return;
    }
    int** c = copyMatrix(m, n);
    for (int i = 0; i < n; i++) {     // swap the two entries in every row
        int temp = c[i][c1];
        c[i][c1] = c[i][c2];
        c[i][c2] = temp;
    }
    printMatrix(c, n);
    freeMatrix(c, n);
}

// ---------- Problem 7: update an element ----------

// Sets element (row, col) (0-indexed) of a copy of m to value and prints it.
// Prints an error instead if either index is out of bounds.
void updateElement(int** m, int n, int row, int col, int value) {
    if (row < 0 || row >= n || col < 0 || col >= n) {
        cout << "Error: row or column index out of bounds" << endl;
        return;
    }
    int** c = copyMatrix(m, n);
    c[row][col] = value;
    printMatrix(c, n);
    freeMatrix(c, n);
}

// ---------- Main program ----------

int main() {
    char filename[256];
    cout << "Enter input filename: ";
    cin >> filename;

    int n;
    int** a;
    int** b;
    if (!loadMatrices(filename, n, a, b))
        return 1;                     // stop if the file couldn't be read

    cout << "\nMatrix A:" << endl;
    printMatrix(a, n);

    cout << "\nMatrix B:" << endl;
    printMatrix(b, n);

    cout << "\nA + B:" << endl;
    addMatrices(a, b, n);

    cout << "\nA * B:" << endl;
    multiplyMatrices(a, b, n);

    cout << "\nDiagonal sums for Matrix A:" << endl;
    diagonalSums(a, n);

    // Each of the following works on the original matrix A.
    cout << "\nProblem 5 - Rows 0 and 2 swapped:" << endl;
    swapRows(a, n, 0, 2);

    cout << "\nProblem 6 - Columns 0 and 2 swapped:" << endl;
    swapColumns(a, n, 0, 2);

    cout << "\nProblem 7 - Updated matrix:" << endl;
    updateElement(a, n, 1, 2, 99);

    // Release the memory we allocated.
    freeMatrix(a, n);
    freeMatrix(b, n);
    return 0;
}
