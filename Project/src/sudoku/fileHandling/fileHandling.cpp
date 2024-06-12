#include <iostream>

#include "fileHandling.h"

SudokuFileHandler::SudokuFileHandler() {}

SudokuMatrix SudokuFileHandler::getSudokuMatrixFromFile(std::string filePath) {
	std::ifstream inputFile{filePath};
	nlohmann::json inputJson;
	try {
		inputJson = nlohmann::json::parse(inputFile);
	} catch (const std::exception &e) {
		std::cerr << e.what() << "\n";
		SudokuMatrix sudokuMatrix{};

		return sudokuMatrix;
	}

	SudokuMatrix inputMatrix{inputJson.at("sudokuSubMatrixSize")};
	for (int i{0}; i < inputMatrix.getSize(); i++) {
		for (int j{0}; j < inputMatrix.getSize(); j++) {
			try {
				inputMatrix.getCellAtPosition(std::pair<int, int>{i, j})->setValue(inputJson.at(std::to_string(i) + "," + std::to_string(j)));
			} catch (const std::exception &e) {
				std::cerr << e.what() << "\n";
				inputMatrix.getCellAtPosition(std::pair<int, int>{i, j})->setValue(0);
			}

			try {
				if (inputJson.at(std::to_string(i) + "," + std::to_string(j) + "_lock")) {
					inputMatrix.getCellAtPosition(std::pair<int, int>{i, j})->lock();
				}
			} catch (const std::exception &e) {
				std::cerr << e.what() << "\n ";
			}

			try {
				if (inputJson.at(std::to_string(i) + "," + std::to_string(j) + "_parityCellsPresent")) {
					int parityCellsAmount = inputJson.at(std::to_string(i) + "," + std::to_string(j) + "_parityCellsAmount");
					for (int k{0}; k < parityCellsAmount; k++) {
						inputMatrix.getCellAtPosition(std::pair<int, int>{i, j})->addParityCell(inputJson.at(std::to_string(i) + "," + std::to_string(j) + "_parityCells_" + std::to_string(k)));
					}
				}
			} catch (const std::exception &e) {
				std::cerr << e.what() << "\n";
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
			} else {
				outputJson[std::to_string(i) + "," + std::to_string(j) + "_lock"] = false;
			}

			if (this->sudokuMatrix->getCellAtPosition(std::pair<int, int>{i, j})->getParityCells().size() > 0) {
				outputJson[std::to_string(i) + "," + std::to_string(j) + "_parityCellsPresent"] = true;
				outputJson[std::to_string(i) + "," + std::to_string(j) + "_parityCellsAmount"] = this->sudokuMatrix->getCellAtPosition(std::pair<int, int>{i, j})->getParityCells().size();
				for (int k{0}; k < this->sudokuMatrix->getCellAtPosition(std::pair<int, int>{i, j})->getParityCells().size(); k++) {
					outputJson[std::to_string(i) + "," + std::to_string(j) + "_parityCells_" + std::to_string(k)] = this->sudokuMatrix->getCellAtPosition(std::pair<int, int>{i, j})->getParityCells().at(k);
				}
			} else {
				outputJson[std::to_string(i) + "," + std::to_string(j) + "_parityCellsPresent"] = false;
			}
		}
	}

	std::ofstream outputFile;
	outputFile.open(filePath);
	outputFile << std::setw(4) << outputJson;
	outputFile.close();

	return this;
}

SudokuFileHandler *SudokuFileHandler::setSudokuMatrix(SudokuMatrix *sudokuMatrix) {
	this->sudokuMatrix = sudokuMatrix;

	return this;
}