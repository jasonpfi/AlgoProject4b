/**
* Team: fitsmu
* Jason Fitch
* Sam Smucny
*
* board.cpp: Implementations of board class methods
*/

#include <fstream>
#include <vector>
#include "board.h"
#include "cell.h"

template<typename T>
ostream &operator<<(ostream &ostr, const vector<T> &v)
// Overloaded output operator for vector class. Prints each element of the
// given vector
{
	for (int i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	std::cout << std::endl;
	return ostr;
}

int squareNumber(const int& i, const int& j)
// Return the square number of cell i,j (counting from left to right,
// top to bottom).  Note that i and j each go from 1 to BoardSize.
// Range of square values is 1 to 9.
{
	return SquareSize * ((i - 1) / SquareSize) + (j - 1) / SquareSize + 1;
}

bool board::isSolved() const
// Checks if a board is completely filled and all the constraints are met.
// Constraints:
//  1) Every Cell has been filled
//  2) There are no conflicts - each number only appears once in each row,
//     column, and square. Conflict checking is done in the algorithm
//     implementation.
{
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			if (value[i - 1][j - 1] == Blank) return false;
		}
	}
   return true;
} // End isSolved

void board::printConflicts() const
// Prints the conflicts of the board to the screen in a table. Prints the
// conflicts for each Row, Columns, and Square in the board
{
	std::cout << "\nConflicts:\n";
	std::cout << "Digit: 1 2 3 4 5 6 7 8 9" << std::endl << std::endl;

	// Conflicts in the rows
	for (int i = 0; i < rows.rows(); i++)
	{
		std::cout << "Row " << i + 1 << ": " << rows[i];
	}
	std::cout << std::endl;

	// Conflicts in the columns
	for (int i = 0; i < cols.rows(); i++)
	{
		std::cout << "Col " << i + 1 << ": " << cols[i];
	}
	std::cout << std::endl;

	// Conflicts in the squares
	for (int i = 0; i < squares.rows(); i++)
	{
		std::cout << "Sqr " << i + 1 << ": " << squares[i];
	}
	std::cout << std::endl;
} // End printConflicts

bool board::solve(heap<cell>& cells, int& count, const bool &first)
// Recursive solving function that traverses the tree of possibilities
// to find sudoku solutions. If first is true then returns immediately
// after the first solution is found. If a solution is not found, then
// the method will backtrack until there are no conflicts and continue to
// solve the board until both Constraints are filled
//
// heap cells: The Heap that contains all the cells for the board
// int count: The number of times that the code has been traversed
// bool first: True if multiple possibilities should not be found - short
//             circuit on the first viable solution
{
	count++;
	if (isSolved())
	{
		print();
		return true;
	}
	else
	{
		cell next(cells.pop());

		int i(next.getRow());
		int j(next.getCol());

		// Try all possibilities
		for (int digit = 1; digit <= 9; digit++)
		{
			if (validPlacement(i, j, digit))
			{
				setCell(i, j, digit);

				// short circuit if a solution is found and we don't want to find all
				if (solve(cells, count, first) && first) return true;

				clearCell(i, j);
			}
		} // End for

		// All possibilities attempted. Backtrack
		cells.push();
		return false;
	} // End else
} // End solve()

void board::clear()
// Mark all possible values as legal for each board entry. The board is empty.
// Next, the input files will be read into each cell in the board.
{
	for (int i = 1; i <= BoardSize; i++)
		for (int j = 1; j <= BoardSize; j++)
		{
			value[i - 1][j - 1] = Blank;
		}
}

void board::initialize(ifstream &fin)
// Read a Sudoku board from the input file stream.
//
// fin: The input file stream to read the values from the data files
{
	char ch;
	vector<cell> newCells(0);

	cols.resize(BoardSize, MaxValue);
	squares.resize(BoardSize, MaxValue);
	rows.resize(BoardSize, MaxValue);
	clear();

	// load each square with a value (or leave blank)
	for (int i = 1; i <= BoardSize; i++)
	{
		for (int j = 1; j <= BoardSize; j++)
		{
			fin >> ch;

			// If the read char is not Blank
			if (ch != '.')
				setCell(i, j, ch - '0');   // Convert char to int
		}
	} // End for
} // End initialize()

void board::clearCell(const int& i, const int& j)
// Sets the value in the cell to blank, updates the conflict list to remove
// conflicts with this number in the column, row, and square
//
// int i: The column of the cell to clear
// int j: The row of the cell to clear
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
	{
		ValueType tmp = value[i - 1][j - 1] - 1;
		value[i - 1][j - 1] = Blank;
		cols[j - 1].at(tmp) = false;
		rows[i - 1].at(tmp) = false;
		squares[squareNumber(i, j) - 1].at(tmp) = false;
	}
	else
		throw rangeError("bad value in clearCell");
} // End clearCell(int, int)

void board::setCell(const int& i, const int& j, const ValueType& val)
// Sets the value in a cell. Throws exception if bad values
// are passed. Updates the conflict matrices with the value that has been
// placed
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize && val >= MinValue
		&& val <= MaxValue)
	{
		value[i - 1][j - 1] = val;
		cols[j - 1].at(val - 1) = true;
		rows[i - 1].at(val - 1) = true;
		int sqNum(squareNumber(i, j) - 1);
		squares[sqNum].at(val - 1) = true;

	}
	else
	{
			throw rangeError("bad value in setCell");
	}
} // End setCell(int, int, ValueType)

ValueType board::getCell(const int& i, const int& j) const
// Returns the value stored in a cell.  Throws an exception
// if bad values are passed.
//
// int i: The columns number of the cell to retrieve
// int j: The row number of the cell to retrieve
{
	if (i >= 1 && i <= BoardSize && j >= 1 && j <= BoardSize)
		return value[i - 1][j - 1];
	else
		throw rangeError("bad value in getCell");
}

bool board::validPlacement(const int &i, const int &j,
		                     const ValueType &val) const
// Tests if a number being placed at the cell specified by the column and row
// is a valid placement - i.e. the number has not been already placed in the
// row, column or square
//
// int i: The Column number of the cell
// int j: The Row number of the cell
// ValueType val: The value being placed in the cell
{
	return !(rows[i - 1][val - 1] || cols[j - 1][val - 1]
	    || squares[squareNumber(i, j) - 1][val - 1]);
}

bool board::isBlank(const int& i, const int& j) const
// Returns true if cell at column number i and row number j
// is blank, and false otherwise.
//
// int i: The Column number of the cell
// int j: The Row number of the cell
{
	if (i < 1 || i > BoardSize || j < 1 || j > BoardSize)
		throw rangeError("bad value in setCell");

	return (getCell(i, j) == Blank);
}

void board::print() const
// Prints the current board. An empty cell is represented by an empty space
// and a filled cell is represented by the value contained in the cell.
// The board is drawn with the characters "-" and "|" representing the sides
// and square-edge barriers
{
	for (int i = 1; i <= BoardSize; i++)
	{
		if ((i - 1) % SquareSize == 0)
		{
			std::cout << " -";
			for (int j = 1; j <= BoardSize; j++)
				std::cout << "---";
			std::cout << "-";
			std::cout << std::endl;
		}
		for (int j = 1; j <= BoardSize; j++)
		{
			if ((j - 1) % SquareSize == 0)
				std::cout << "|";
			if (!isBlank(i, j))
				std::cout << " " << getCell(i, j) << " ";
			else
				std::cout << "   ";
		}
		std::cout << "|";
		std::cout << std::endl;
	}

	std::cout << " -";
	for (int j = 1; j <= BoardSize; j++)
		std::cout << "---";
	std::cout << "-";
	std::cout << std::endl;
} // End print()



