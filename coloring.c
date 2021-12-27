#include <stdio.h>

int main(void){
	
	//Standard in
	FILE* ifp = stdin;
	
	//Initialize the variables
	int dots,lines;
	int i,j;
	int a,b;
	int caseNum;
	
	for (caseNum = 1;; caseNum++) {
	
		//Input the counts
		fscanf(ifp,"%d%d",&dots,&lines);
		
		//If dots and lines are 0, this is the end of the cases
		if(dots+lines == 0) break;
		
		int adj[dots][dots]; //Adjacency array (adj[X][Y] == 1 iff X and Y are connected)
		int deg[dots]; //Degree of each dot (number of lines connected to the dot)
		int max = 0; //Maximum degree of any dot (initialize to 0)
		
		printf("Page #%d:\n",caseNum); //Output the case number
		
		//Initialize the adjacency array and the degree array
		for(i = 0; i < dots; i++) {
			for(j = 0; j < dots; j++){
				adj[i][j] = 0;
			}
			deg[i] = 0;
		}
		
		//Input the lines
		for(i = 0; i < lines; i++){
		
			//Input the two dots to connect
			fscanf(ifp, "%d%d",&a,&b);
			
			//Connect the two dots in the adjacency array
			adj[a-1][b-1] = 1;
			adj[b-1][a-1] = 1;
			
			//Increase the degree of each dot
			deg[a-1]++;
			deg[b-1]++;
			
			//Check if there is a new maximum degree
			if(deg[a-1] > max)
				max = deg[a-1];
			if(deg[b-1] > max)
				max = deg[b-1];
			
		}
		
		//If the number of lines connected to any dot is more than 3, its impossible to bi-color
		if(max > 2){
			printf("No, Arthur can't color it.\n\n");	
		}
		//Simple Bredth First Search, the only way its possible is if the graph is a simple cycle or
		//connected line.
		else {
		
			int seen[dots]; //If the dot has been checked (seen) yet
			for(i = 0; i < dots; i++)
				seen[i] = 0; //Initialize to not checked (seen) yet
			
			int can = 1; //Initialize whether the graph is valid for bi-coloring
			
			while(1) {
				int d = -1; //The next unchecked (unseen) dot
				for(i = 0; i < dots; i++) {
					if(!seen[i]){
						d = i;
						break;
					}
				}
				if(d == -1) //If all dots have been checked (seen), we are done checking
					break;
				
				int Q[dots]; // Queue
				int C[dots]; // Colors
				for(i = 0; i < dots; i++)
					C[i] = 0;
				int s = 0, e = 0;
				Q[e++] = d;
				seen[d] = 1;
				
				//Loop through each dot in the "line"
				while(s != e){
					int v = Q[s++];
					for(i = 0; i < dots; i++){
						if(adj[v][i] && !seen[i]){
							seen[i] = 1;
							Q[e++] = i;
							
							if(C[v] == 0){ //If the node is our start, color the first edge with a red
								C[v] = 1;
								C[i] = 1;
							}
							else if(C[i] == 0) { //If the node we are connecting to has no colored edges, color it with the opposite color
								C[i] = 3 - C[v];
								C[v] = 3;
							}
							else if(C[i] == C[v]){ //The two nodes have same colored edges connected to them
								C[i] = 3;
								C[v] = 3;
							}
							else{ //Edge cannot be either color, so it is impossible
								can = 0;
								s = e;
								break;
							}
						}
						
						if(adj[v][i]) {
							if(C[i]+C[v] == 3){
								can = 0;
								s = e;
								break;
							}
						}
					}
				}
				
				if(!can)
					break;
				
			}
			if(can)
				printf("Yes, Arthur can color it.\n\n");
			else
				printf("No, Arthur can't color it.\n\n");
		}
	}
	return 0;
}
