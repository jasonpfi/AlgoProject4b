/**
* Team: fitsmu
* Jason Fitch
* Sam Smucny
*
* board.h: Declaration of soduku board class
*/

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "d_matrix.h"
#include "heap.h"

// The type of the value in a cell
typedef int ValueType;

// Indicates that a cell is blank
const int Blank = -1;

// The number of cells in a small sqare (usually 3). The board has SquareSize^2
// rows and SquareSize^2 columns
const int SquareSize = 3;

// The board size, in terms of length and width - equal to SquareSize^2
const int BoardSize = SquareSize * SquareSize;

// Possible values for each cell
const int MinValue = 1;
const int MaxValue = BoardSize;

class cell;

// Stores the entire Sudoku board
class board
{
public:

	// Board class constructor. Sets the size of the value matrix and conflict
	// matrices
	board(int sqSize): value(BoardSize, BoardSize), rows(BoardSize),
	                   cols(BoardSize), squares(BoardSize)
	{
			clear();
	}

	void clear();
	void initialize(ifstream &);
	void print() const;
	bool isBlank(const int&, const int&) const;
	ValueType getCell(const int&, const int&) const;
	bool validPlacement(const int&, const int&, const ValueType&) const;
	void getNextCell(int& i, int& j);
	void setCell(const int&, const int&, const ValueType&);
	void clearCell(const int&, const int&);
	bool isSolved() const;
	void printConflicts() const;
	bool solve(heap<cell>&, int&, const bool& = false);

private:

	// The following matrices go from 1 to BoardSize in each
	// dimension, i.e., they are each (BoardSize) * (BoardSize)

	// Sudoku board values
	matrix<ValueType> value;

	// Conflict Vectors
	matrix<bool> rows;
	matrix<bool> cols;
	matrix<bool> squares;
};
