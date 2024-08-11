#include "Helpers.h"

const double SqrtF(float n)
{
	if (n == 0) {
		return 0;
	}
	if (n < 0) {
		n *= -1;
	}

	//lower closest perfect square's root
	int a = 0;
	//temporary holder for division
	double s = 0;
	//Holds the value of n to be calculate against
	float nt = n;

	//find a
	for (int p = 1; p < n; p+=2) { //add 2 to p after every iteration
		//subtract consequent odd numbers (p) from nt, and add to a until nt-p will
		//result in a number less than or equal to 0
		
		if (nt - p > 0) { //checks if the next subtraction will result in a number greater than 0
			nt -= p;
		}
		else {
			break;
		}

		a++;
	}

	if (n - (a * a) == 0) { //if the number is a perfect square, exits
		return a;
	}
	nt = n; // reset nt to n for more calculations

	//divide nt by a, and then get the average of a and nt/a || (a+nt)/2

	//adjust float precision to 5 decimals

	s = ((nt / a) + a) / 2; //Sets s to the average of (nt/a) + a

	while ((s * s) >= n + 0.000001) {
		s = ((nt/s) + s) / 2;
	}

	return s;
}
