/**
 * Team: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * Cell Header file - contains the declarations of methods and data members
 *    of the Cell class
 */

#pragma once
#include "board.h"

// cell class
class cell
{
public:

	// Constructor - sets the column, row, and board that this cell belongs to
	//
	// board *parent - The board that this cell belongs to
	// int i - the row that this cell is in
	// int j - the column that this cell is in
	cell(board *parent, const int& i, const int& j) :
		row(i), col(j), b(parent)
	{}

	// Empty Constructor
	cell() {}

	// Returns the Row of the Cell
	int getRow() const { return row; }
	// Returns the Column of the Cell
	int getCol() const { return col; }

	// Returns the number of possible digits that could be placed in this cell
	int candidateDigits() const;

	// Finds if there are more candidate digits in cell b than in cell a
	friend bool operator> (const cell& a, const cell& b);

private:

	// Private data members of the Cell - Position in the row and column and the
	//  parent board
	board *b;
	int row;
	int col;
}; // End cell class definition

