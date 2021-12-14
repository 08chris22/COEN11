//Christian Garcia COEN 11L Tuesday 2:15
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main ()

	{
	int divisor;
	int quotient;
	int dividend;
	int score=0;
	int i;
	srand ((int)time(NULL));

	for (i=0;i<10;i++)
		{
		divisor = rand () % 12+ 1;
		quotient = rand () % 13;
		dividend=quotient*divisor;
		score+=10*division(dividend, divisor, quotient);
		}
	printf ("You got %d%%\n", score);
	}

int division (int dividend, int divisor, int quotient)
	{
	int answer;
	printf ("What is %d divided by %d?\n", dividend, divisor);
	scanf ("%d",&answer);
	if (answer == quotient)
		{
		printf ("Great!\n");
		}
	else
		{
		printf ("Sorry, the correct answer is %d.\n", quotient);
		}

	if (answer==quotient)
		{
		return 1;
		}
	return 0;
	}
