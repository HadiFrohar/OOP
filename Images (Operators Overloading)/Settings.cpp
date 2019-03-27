#include "Settings.h"

int extractMax(int s1, int s2)
{
	if (s1 >= s2)
		return s1;
	else
		return s2;
}

int extractMin(int s1, int s2)
{
	if (s1 <= s2)
		return s1;
	else
		return s2;
}
