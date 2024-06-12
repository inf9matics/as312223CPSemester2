#include "fileHandling.h"

SudokuFileHandler::SudokuFileHandler() {}

SudokuMatrix SudokuFileHandler::getSudokuMatrixFromFile(std::string filePath) {
	std::ifstream inputFile{filePath};
	nlohmann::json inputJson = nlohmann::json::parse(inputFile);

	SudokuMatrix inputMatrix{inputJson.at("sudokuSubMatrixSize")};
	for (int i{0}; i < inputMatrix.getSize(); i++) {
		for (int j{0}; j < inputMatrix.getSize(); j++) {
			inputMatrix.getCellAtPosition(std::pair<int, int>{i, j})->setValue(inputJson.at(std::to_string(i) + "," + std::to_string(j)));

			if (inputJson.at(std::to_string(i) + "," + std::to_string(j) + "_lock")) {
				inputMatrix.getCellAtPosition(std::pair<int, int>{i, j})->lock();
			}
		}
	}

	return inputMatrix;
}

SudokuFileHandler *SudokuFileHandler::setSudokuMatrixToFile(std::string filePath) {
	nlohmann::json outputJson;

	outputJson["sudokuSubMatrixSize"] = this->sudokuMatrix->getSubMatrixSize();
	for (int i{0}; i < this->sudokuMatrix->getSize(); i++) {
		for (int j{0}; j < this->sudokuMatrix->getSize(); j++) {
			outputJson[std::to_string(i) + "," + std::to_string(j)] = this->sudokuMatrix->getCellAtPosition(std::pair<int, int>{i, j})->getValue();

			if (this->sudokuMatrix->getCellAtPosition(std::pair<int, int>{i, j})->getLocked()) {
				outputJson[std::to_string(i) + "," + std::to_string(j) + "_lock"] = true;
			}
            else {
                outputJson[std::to_string(i) + "," + std::to_string(j) + "_lock"] = false;
            }
		}
	}

	std::ofstream outputFile;
	outputFile.open(filePath);
	outputFile << outputJson;
	outputFile.close();

	return this;
}

SudokuFileHandler *SudokuFileHandler::setSudokuMatrix(SudokuMatrix *sudokuMatrix) {
	this->sudokuMatrix = sudokuMatrix;

	return this;
}