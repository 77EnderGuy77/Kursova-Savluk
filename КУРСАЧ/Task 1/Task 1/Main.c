#include "Header.h"

int main() {
	int menu, choice;
	do
	{
		printf("Choose your task:\n 1 - Task 1 \n 2 - Task 2\n");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1: Num1();
			break;
		case 2: Num2();
			break;
		default: puts("Enter correct choice");
		}
		printf("Do you want to exit?\n0 - yes; 1 - no \n");
		scanf_s("%d", &menu);
	} while (menu != 0);
	return 0;
}