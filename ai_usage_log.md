# AI Usage Log

**Platform:** Claude (claude.ai chat interface)  
**Model:** Claude Sonnet 5.5

---

## Interaction 1

### User

```
EECS 348: Software Engineering - Fall 2026
Lab 5 - C++ Programming
Objective: Get familiar with C++ programming and practice Git and make again. During the C++ programming, you will practice the basic file operations, if-statement, loop, function calls, and output format control.
What to turn in: Please provide a URL to your GitHub repository. If you are unable to push your code to GitHub, you may instead use KU GitLab, which works in a very similar way. Your repository must be private so that your work is not publicly searchable. Limit access to yourself, the course instructor, and the course GTAs. Make sure your GTA has access to review and grade your submission.
Grading:

* Each of the first two questions is worth 10 points, and each of the remaining questions is worth 15 points. [95 points]
* A valid Makefile must be included in the repository (similar to the Makefile for C, but replace the compiler gcc with g++). [5 points]

Programming problem: Matrix Operations
1. Read values from a file into the matrix:
Implement a function to load matrix data from a user-specified file (you can use fstream/ifstream). The first line of the file should contain an integer N indicating the size of the matrices, followed by two N × N matrices. After reading the file, print the matrices with proper formatting, such as aligned columns. Note that N can be any valid positive integer.
2. Add two matrices and display the result:
Implement a function that adds two matrices (you can use vector, i.e., the dynamic array, to store the matrix) and displays the resulting matrix.
3. Multiply two matrices and display the result:
Implement a function that multiplies two matrices and displays the resulting matrix.
Please refer to the link for the matrix multiplication: https://www.mathsisfun.com/algebra/matrix-multiplying.html
4. Get the sums of matrix diagonal elements:
Implement a function that calculates and displays, separately, the sum of the main diagonal elements and the sum of the secondary diagonal elements of a matrix.
5. Swap matrix rows and display the result:
Implement a function that takes a matrix and two row indices as input (with indexing starting at 0). If both indices are within valid bounds, swap the specified rows and output the resulting matrix.
6. Swap matrix columns and display the result:
Implement a function that takes a matrix and two column indices as input (with indexing starting at 0). If both indices are within valid bounds, swap the specified columns and output the resulting matrix.
7. Update a matrix element and display the result:
Implement a function that accepts a matrix, a row index, a column index, and a new value. If both indices are valid (with indexing starting at 0), update the element at the specified position and display the resulting matrix.
Sample Input
4 // The size of the square matrix (N) and the input file should not include this comment
01 02 03 04
05 06 07 08
09 10 11 12
13 14 15 16
13 14 15 16
09 10 11 12
05 06 07 08
01 02 03 04
```

### Assistant Summary

Created a C++ program (`matrix_ops.cpp`) implementing all seven problems using `vector<vector<int>>`: loading N and two matrices from a user-specified file with error checks, aligned matrix printing, matrix addition, matrix multiplication, main and secondary diagonal sums, row swap, column swap, and element update, with bounds checks on the swaps and update. Also created a Makefile using `g++`, and a sample `input.txt` based on the provided sample data. Compiled and ran the program on the sample input and reported results such as A·B's first row (50 60 70 80) and both diagonal sums (34). Summarized the program's structure and how to build and run it (`make`, `./matrix_ops`, `make clean`). Advised creating a private repository, adding the instructor and GTA as collaborators, and understanding each function before submitting.

---

## Interaction 2

### User

```
reduce the included files to <iostream> and <fstream> and add comments
```

(The message included an attached file, `sample_output.txt`, containing sample program output.)

### Assistant Summary

Rewrote the program so it includes only `<iostream>` and `<fstream>`. Because `<vector>` was no longer allowed, matrices were changed to dynamically allocated 2D arrays (`int**`) with helper functions to allocate, copy, and free them. Replaced `setw` with a custom padding function using a minimum column width of 4. Added comments throughout. Changed the demo output to follow the attached sample output (prompt text, headings, rows 0 and 2 swapped, columns 0 and 2 swapped, element (1,2) set to 99). Compiled the program and confirmed its output matched `sample_output.txt` (ignoring trailing whitespace). Noted that the Makefile and `input.txt` were unchanged.

---

## Interaction 3

### User

(No text was included in this message. The message attached a file, `Lab5_Companion_Guide__1_.pdf`.)

### Assistant Summary

Updated the project to match the attached companion guide: renamed `matrix_ops.cpp` to `main.cpp`, changed the Makefile to build a `main` target, changed file-related error messages to `cerr` (bad-index messages remained on `cout`), added a `.gitignore` containing `main`, and generated `output.txt` from the sample input. Ran tests for N = 1, N = 2, negative entries, a missing file, N = 0, and a file with too few values, and reported the results (for example, for N = 1: A+B = [7], A·B = [12], both diagonal sums 3). Noted that the guide's instruction to make the repository public conflicts with the lab handout's requirement that it be private, and suggested following the handout and confirming with the instructor or GTA. Noted that the guide's checklist mentions an AI log section that the student would need to complete, and recommended being honest about AI use in it. Recommended that the student test small cases by hand and be able to explain the code.

---

## Interaction 4

### User

```
it should run how the instructions want
```

### Assistant Summary

No assistant response to this message appears in the available conversation history.

---

## Interaction 5

### User

```
it should allow for input when needed and output the output.txt
```

### Assistant Summary

Rewrote `main.cpp` so the program prompts for input: the filename, two row indices to swap, two column indices to swap, and a row, column, and new value for the update. The printing functions were changed to take an output stream, and a report function writes the full results to both the screen and `output.txt` (created by the program with `ofstream`). Headings now use the entered indices (for example, "Problem 5 - Rows 0 and 2 swapped:"). Invalid indices print a "not swapped" or "not updated" heading with an error message and leave the matrix unchanged, and non-numeric input prints an error and stops. Tested with the sample input and indices matching the sample output and confirmed the generated `output.txt` matched `sample_output.txt` apart from the prompt line; also tested invalid indices and non-numeric input. Advised not to also redirect output with `> output.txt`, since the program creates that file itself. Stated that the Makefile, `.gitignore`, and `input.txt` were unchanged.

---

## Interaction 6

### User

(No text was included in this message. The message attached a file, `AI_USAGE_LOG_INSTRUCTIONS-1.md`, containing instructions for generating an AI usage log.)

### Assistant Summary

Generated this AI usage log as `ai_usage_log.md`, documenting the conversation history available.

---
