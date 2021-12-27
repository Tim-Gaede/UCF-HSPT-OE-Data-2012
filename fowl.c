/*
 *Program: fowl
 *Language: C
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
	//standard in
	FILE* fin = stdin;

	//read in the number of Targets
	int crnt,numTargets;
	fscanf(fin, "%d", &numTargets);

	//loop through each target
	for(crnt=1; crnt<=numTargets; crnt++) {
		//for each target, read in the three side lengths
		int a,b,c;
		fscanf(fin, "%d %d %d", &a, &b, &c);
		
		//square each of the side lengths
		int a2 = a*a;
		int b2 = b*b;
		int c2 = c*c;

		//if any of the squares is the sum of the other two
		//the target can be hit
		//otherwise it cannot
		if((a2+b2==c2) || (a2+c2==b2) || (b2+c2==a2))
			printf("Target #%d: YES\n", crnt);
		else
			printf("Target #%d: NO\n", crnt);
	}
}
