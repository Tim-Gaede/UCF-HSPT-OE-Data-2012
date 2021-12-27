#include<stdio.h>

int main() {

	//Initialize the file reader
    FILE* f = stdin;

	//Input the number of cases
	int T;
	fscanf(f,"%d",&T);
	
	//Loop through each case
	int t;
	for (t=0; t<T; t++) {
	
		//Input the person's name
		char name[101];
		fscanf(f,"%s",name);
		
		
		//Output the case number
		printf("Name #%d:\n",t+1);
		
		//Output the person's like of the smell of adventure
		printf("Does %s like the smell of adventure? Of course they do.\n\n",name);
		
	}
	
	return 0;
	
}
