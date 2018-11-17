

#include <iostream>
#include <fstream>
#include <vector>
#include "heap.h"
#include "board.h"

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
	/*vector<int> ints({ 1, 3, 6, 2, 4 });
	heap<int> h(ints);

	std:cout << h.heapsort();*/

	// declare input file to read
	ifstream fin;

	// Read the grid from the file.
	string fileName = "data/sudoku1-3.txt";
	std::cout << "Reading " << fileName << std::endl;

	fin.open(fileName.c_str());
	if (!fin)
	{
		cerr << "Cannot open " << fileName << std::endl;
		exit(1);
	}

	try
	{
		board b(SquareSize);

		while (fin && fin.peek() != 'Z')
		{
			// initialize board and print information to console
			b.initialize(fin);

			b.print();

			b.printConflicts();

			int count(0);
			b.solve(count);
			std::cout << "Recursive calls: " << count << std::endl;

			// check if the board is solved
			if (b.isSolved())
			{
				std::cout << "The board has been solved!" << std::endl;
			}
			else
			{
				std::cout << "The board has NOT been solved." << std::endl;
			}
		}
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

