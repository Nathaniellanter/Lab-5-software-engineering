// EECS 348 Lab 5 - Matrix Operations
// Only <iostream> and <fstream> are used, so matrices are stored as
// dynamically allocated 2D arrays (int**) instead of std::vector.
//
// Program flow:
//   1. Ask for the input file name and load matrices A and B.
//   2. Ask for the indices/values needed by problems 5, 6 and 7.
//   3. Print the full set of results to the screen AND save the same
//      text to output.txt.
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
// Every printing function takes an ostream& so the same code can write
// to the screen (cout) or to a file (ofstream).

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
void printPadded(ostream& out, int v, int width) {
    for (int s = numLength(v); s < width; s++)
        out << ' ';
    out << v;
}

// Print a matrix with aligned columns. The column width is at least 4
// and grows if the matrix contains wider numbers.
void printMatrix(ostream& out, int** m, int n) {
    int width = 4;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (numLength(m[i][j]) + 1 > width)
                width = numLength(m[i][j]) + 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printPadded(out, m[i][j], width);
        out << endl;
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
void addMatrices(ostream& out, int** a, int** b, int n) {
    int** c = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
    printMatrix(out, c, n);
    freeMatrix(c, n);
}

// ---------- Problem 3: multiply two matrices ----------

// Prints a * b. Element (i,j) is the dot product of row i of a
// with column j of b.
void multiplyMatrices(ostream& out, int** a, int** b, int n) {
    int** c = createMatrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                c[i][j] += a[i][k] * b[k][j];
    printMatrix(out, c, n);
    freeMatrix(c, n);
}

// ---------- Problem 4: diagonal sums ----------

// Prints the sum of the main diagonal (top-left to bottom-right) and
// the secondary diagonal (top-right to bottom-left).
void diagonalSums(ostream& out, int** m, int n) {
    int mainSum = 0;
    int secondarySum = 0;
    for (int i = 0; i < n; i++) {
        mainSum += m[i][i];               // elements (0,0), (1,1), ...
        secondarySum += m[i][n - 1 - i];  // elements (0,n-1), (1,n-2), ...
    }
    out << "Main diagonal sum: " << mainSum << endl;
    out << "Secondary diagonal sum: " << secondarySum << endl;
}

// ---------- Problem 5: swap rows ----------

// Swaps rows r1 and r2 (0-indexed) of a copy of m and prints it.
// If either index is out of bounds, prints an error and changes nothing.
void swapRows(ostream& out, int** m, int n, int r1, int r2) {
    if (r1 < 0 || r1 >= n || r2 < 0 || r2 >= n) {
        out << "Problem 5 - Rows " << r1 << " and " << r2
            << " not swapped:" << endl;
        out << "Error: row index out of bounds" << endl;
        return;
    }
    out << "Problem 5 - Rows " << r1 << " and " << r2 << " swapped:" << endl;
    int** c = copyMatrix(m, n);
    int* temp = c[r1];                // swapping row pointers swaps whole rows
    c[r1] = c[r2];
    c[r2] = temp;
    printMatrix(out, c, n);
    freeMatrix(c, n);
}

// ---------- Problem 6: swap columns ----------

// Swaps columns c1 and c2 (0-indexed) of a copy of m and prints it.
// If either index is out of bounds, prints an error and changes nothing.
void swapColumns(ostream& out, int** m, int n, int c1, int c2) {
    if (c1 < 0 || c1 >= n || c2 < 0 || c2 >= n) {
        out << "Problem 6 - Columns " << c1 << " and " << c2
            << " not swapped:" << endl;
        out << "Error: column index out of bounds" << endl;
        return;
    }
    out << "Problem 6 - Columns " << c1 << " and " << c2 << " swapped:" << endl;
    int** c = copyMatrix(m, n);
    for (int i = 0; i < n; i++) {     // swap the two entries in every row
        int temp = c[i][c1];
        c[i][c1] = c[i][c2];
        c[i][c2] = temp;
    }
    printMatrix(out, c, n);
    freeMatrix(c, n);
}

// ---------- Problem 7: update an element ----------

// Sets element (row, col) (0-indexed) of a copy of m to value and prints it.
// If either index is out of bounds, prints an error and changes nothing.
void updateElement(ostream& out, int** m, int n, int row, int col, int value) {
    if (row < 0 || row >= n || col < 0 || col >= n) {
        out << "Problem 7 - Matrix not updated:" << endl;
        out << "Error: row or column index out of bounds" << endl;
        return;
    }
    out << "Problem 7 - Updated matrix:" << endl;
    int** c = copyMatrix(m, n);
    c[row][col] = value;
    printMatrix(out, c, n);
    freeMatrix(c, n);
}

// ---------- Report ----------

// Writes the complete set of results to the given stream. Called once for
// the screen and once for output.txt so both contain identical text.
void writeReport(ostream& out, int** a, int** b, int n,
                 int r1, int r2, int c1, int c2,
                 int uRow, int uCol, int uVal) {
    out << "Matrix A:" << endl;
    printMatrix(out, a, n);

    out << "\nMatrix B:" << endl;
    printMatrix(out, b, n);

    out << "\nA + B:" << endl;
    addMatrices(out, a, b, n);

    out << "\nA * B:" << endl;
    multiplyMatrices(out, a, b, n);

    out << "\nDiagonal sums for Matrix A:" << endl;
    diagonalSums(out, a, n);

    // Each of the following works on the original matrix A.
    out << endl;
    swapRows(out, a, n, r1, r2);

    out << endl;
    swapColumns(out, a, n, c1, c2);

    out << endl;
    updateElement(out, a, n, uRow, uCol, uVal);
}

// ---------- Main program ----------

int main() {
    // Ask for the file and load both matrices.
    char filename[256];
    cout << "Enter input filename: ";
    cin >> filename;

    int n;
    int** a;
    int** b;
    if (!loadMatrices(filename, n, a, b))
        return 1;                     // stop if the file couldn't be read

    // Ask for the values needed by problems 5, 6 and 7.
    int r1, r2, c1, c2, uRow, uCol, uVal;

    cout << "Enter two row indices to swap (0-" << n - 1 << "): ";
    if (!(cin >> r1 >> r2)) {
        cerr << "Error: please enter whole numbers" << endl;
        return 1;
    }
    cout << "Enter two column indices to swap (0-" << n - 1 << "): ";
    if (!(cin >> c1 >> c2)) {
        cerr << "Error: please enter whole numbers" << endl;
        return 1;
    }
    cout << "Enter row, column and new value to update: ";
    if (!(cin >> uRow >> uCol >> uVal)) {
        cerr << "Error: please enter whole numbers" << endl;
        return 1;
    }

    // Show the results on the screen.
    cout << endl;
    writeReport(cout, a, b, n, r1, r2, c1, c2, uRow, uCol, uVal);

    // Save the same results to output.txt.
    ofstream outFile("output.txt");
    if (outFile) {
        writeReport(outFile, a, b, n, r1, r2, c1, c2, uRow, uCol, uVal);
        cout << "\nResults saved to output.txt" << endl;
    } else {
        cerr << "Error: could not create output.txt" << endl;
    }

    // Release the memory we allocated.
    freeMatrix(a, n);
    freeMatrix(b, n);
    return 0;
}
