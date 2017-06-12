/* To investigate the performace between using if-else case and switch case.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// #define MAX_COUNT (1 << 26)
#define MAX_COUNT 500000000

long long counter = 0;

void switch_case()
{
	int i;
	int c;

	for (i = 0; i < MAX_COUNT; i++) {

		c = i % 20;

		switch (c) {
			case 1: counter += 10; 		break;
			case 2: counter += 55; 		break;
			case 3: counter += 90; 		break;
			case 4: counter += 23; 		break;
			case 5: counter += 41; 		break;
			case 6: counter += 35; 		break;
			case 7: counter += 23; 		break;
			case 8: counter += 87; 		break;
			case 9: counter += 25; 		break;
			case 10: counter += 15; 	break;
			case 11: counter += 32; 	break;
			case 12: counter += 25; 	break;
			case 13: counter += 12; 	break;
			case 14: counter += 34; 	break;
			case 15: counter += 41; 	break;
			case 16: counter += 54; 	break;
			case 17: counter += 32; 	break;
			case 18: counter += 44; 	break;
			case 19: counter += 38; 	break;
			case 20: counter += 99; 	break;
		}
	}
}

void if_else_case()
{
	size_t i;
	size_t c;

	for (i = 0; i < MAX_COUNT; i++) {

		c = i % 20;

		if (c == 1) { counter += 10; }
		else if (c == 2) { counter += 55; }
		else if (c == 3) { counter += 90; }
		else if (c == 4) { counter += 23; }
		else if (c == 5) { counter += 41; }
		else if (c == 6) { counter += 35; }
		else if (c == 7) { counter += 23; }
		else if (c == 8) { counter += 87; }
		else if (c == 9) { counter += 25; }
		else if (c == 10) { counter += 15; }
		else if (c == 11) { counter += 32; }
		else if (c == 12) { counter += 25; }
		else if (c == 13) { counter += 12; }
		else if (c == 14) { counter += 34; }
		else if (c == 15) { counter += 41; }
		else if (c == 16) { counter += 54; }
		else if (c == 17) { counter += 32; }
		else if (c == 18) { counter += 44; }
		else if (c == 19) { counter += 38; }
		else if (c == 20) { counter += 99; }
	}
}

int main()
{

#ifdef _S
	printf("Starting switch case\n");
	switch_case();
	printf("counter: %lld\n", counter);
#elif _I
	printf("Starting if-else case\n");
	if_else_case();
	printf("counter: %lld\n", counter);
#endif
	return 0;
}
