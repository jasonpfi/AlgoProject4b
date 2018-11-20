/**
 * Team: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * fitsmu-4b.cpp: The main file that solves the soduku files, outputs their
 * solutions, and how many iterations it took to solve
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "heap.h"
#include "board.h"
#include "cell.h"

template<typename T>
ostream &operator<<(ostream &ostr, const vector<T> &v)
// Overloaded output operator for vector class.
{
	for (int i = 0; i < v.size(); i++)
		ostr << v[i] << " ";
	std::cout << std::endl;
	return ostr;
}

int main()
// Main method, solves all of the boards in the input file
{
	// declare input file to read
	ifstream fin;

	// Read the grid from the file.
	string fileName = "data/sudoku.txt";
	std::cout << "Reading " << fileName << std::endl;

	// Make sure that the file can be opened
	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << std::endl;
		exit(1);
	}

	try
	{
		long totalCalls(0);
		int numBoards(0);

		// While there is still information in the file to read
		while (fin && fin.peek() != 'Z')
		{
			// initialize board and print information to console
			board b(SquareSize);
			numBoards++;
			b.initialize(fin);

			// If the cell is empty, add the cell to the vector of empty cells
			vector<cell> vCells(0);
			for (int i = 1; i <= 9; i++)
				for (int j = 1; j <= 9; j++)
					if (b.isBlank(i,j))
						vCells.push_back(cell(&b, i, j));

			// Create a heap with all of the empty cells
			heap<cell> cells(vCells);

			// Print the unsolved board with given information
			b.print();

			// Solve the board and count the number of recursive calls
			int count(0);
			b.solve(cells, count, true);
			std::cout << "Recursive calls: " << count << std::endl;
			totalCalls += count;
		} // End While

		// Print statistics for each board
		std::cout << "Total Calls: " << totalCalls << std::endl;
		std::cout << "Avg Calls: " << (1.0*totalCalls) / numBoards << std::endl;
	}

	// The numbers given were out of the range of the board, print exception
	catch (indexRangeError &ex)
	{
		std::cout << ex.what() << std::endl;
		fin.close();
		exit(1);
	}

	// Close the file
	std::cout << std::endl << std::endl;
	fin.close();
} // End Main

