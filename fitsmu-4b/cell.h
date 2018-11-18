#pragma once
#include "board.h"

class cell
{
public:
	cell(board *parent, const int& i, const int& j) :
		row(i), col(j), b(parent)
	{}

	cell() {}

	int getRow() const { return row; }
	int getCol() const { return col; }

	int candidateDigits() const;

	friend bool operator> (const cell& a, const cell& b);

private:
	board *b;
	int row;
	int col;
};

