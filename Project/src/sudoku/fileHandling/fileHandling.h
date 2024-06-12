#ifndef SUDOKU_FILE_HANDLING
#define SUDOKU_FILE_HANDLING

#include <fstream>

#include "json.hpp"
#include "sudoku.h"

class SudokuFileHandler {
      protected:
	SudokuMatrix *sudokuMatrix;

      public:
	SudokuFileHandler();

    SudokuMatrix getSudokuMatrixFromFile(std::string filePath);
    SudokuFileHandler *setSudokuMatrixToFile(std::string filePath);

    SudokuFileHandler *setSudokuMatrix(SudokuMatrix *sudokuMatrix);
};

#endif