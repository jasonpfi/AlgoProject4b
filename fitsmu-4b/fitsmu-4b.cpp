

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
{
	// declare input file to read
	ifstream fin;

	// Read the grid from the file.
	string fileName = "data/sudoku.txt";
	std::cout << "Reading " << fileName << std::endl;

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
		while (fin && fin.peek() != 'Z')
		{
			// initialize board and print information to console
			board b(SquareSize);
			numBoards++;
			b.initialize(fin);
			vector<cell> vCells(0);
			for (int i = 1; i <= 9; i++)
				for (int j = 1; j <= 9; j++)
					if (b.isBlank(i,j))
						vCells.push_back(cell(&b, i, j));
			heap<cell> cells(vCells);

			b.print();

			//b.printConflicts();

			int count(0);
			b.solve(cells, count, true);
			std::cout << "Recursive calls: " << count << std::endl;
			totalCalls += count;
		}

		std::cout << "Total Calls: " << totalCalls << std::endl;
		std::cout << "Avg Calls: " << (1.0*totalCalls) / numBoards << std::endl;
	}
	catch (indexRangeError &ex)
	{
		std::cout << ex.what() << std::endl;
		fin.close();
		exit(1);
	}

	std::cout << std::endl << std::endl;
	fin.close();
}

