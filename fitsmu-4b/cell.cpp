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
// Finds if there are more candidate digits in cell b than in cell a
{
	return a.candidateDigits() < b.candidateDigits();
}


int cell::candidateDigits() const
// Returns the number of possible digits that could be placed in this cell
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
