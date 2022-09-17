#include <stdio.h>
#include "Application/app.h"

#pragma warning( disable : 4996 )

void main(void) {
	while (1)
	{
		appStart();

		char again = 0;
		printf("\n\t****Do you want to make a new transaction? (Y/N)****\n");
		scanf(" %c", &again);
		if (again == 'Y' || again == 'y') {
			continue;
		}
		else
		{
			return;
		}

	}
}