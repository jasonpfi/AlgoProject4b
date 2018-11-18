#include "cell.h"

bool operator> (const cell& a, const cell& b)
{
	return a.candidateDigits() < b.candidateDigits();
}

int cell::candidateDigits() const
{
	int candidates(0);
	if (!b->isBlank(row, col)) return candidates;
	for (int i = 1; i <= 9; i++)
	{
		if (b->validPlacement(row, col, i))
			candidates++;
	}
	return candidates;
};