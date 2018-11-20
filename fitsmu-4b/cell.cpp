/**
 * Team: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * cell.cpp: contains the definitions of the methods that were declared in the
 *  header file
 */

#include "cell.h"

bool operator> (const cell& a, const cell& b)
// Finds if there are more candidate digits in cell b than in cell a.
// This comparator is used in maxHeapify to sort the cells
//
// cell a: first cell to compare
// cell b: second cell to compare
{
	return a.candidateDigits() < b.candidateDigits();
}


int cell::candidateDigits() const
// Returns the number of possible digits that could be placed in this cell
// This is used for sorting the cells in the heap to find the most constrained
// cell. This cell has the least amount of possible digits, so it is more likely
// to pick the correct choice for the value
{
	int candidates(0);
	if (!b->isBlank(row, col))
	{
			return candidates;
	}

	for (int i = 1; i <= 9; i++)
	{
		if (b->validPlacement(row, col, i))
			candidates++;
	}

	return candidates;
} // End candidateDigits
