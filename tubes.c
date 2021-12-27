#include <stdio.h>

#define INF 1000000000

int min(int a, int b);
int max(int a, int b);

int main(){
   //Standard in
   FILE *fin;
   fin = stdin;
   
   int n, t, cnt = 1;
   fscanf(fin, "%d %d", &n, &t);
   
   while(n!=0 && t!=0){
      int largestTube[50]; //This will keep track of the largest cat that can reach a computer
      int visited[50]; //We'll be using this array to mark computers we've already visited
      int internet[50][50]; //An adjacency matrix to represent connections between computers. If i is connected to j, internet[i][j] will be greater than zero (this value is actually the size of the tube connecting the two).
      
      int i, j;
      
      //Initialize all arrays
      for(i = 0; i < n; i++){
         largestTube[i] = 0;
         visited[i] = 0;
         for(j = 0; j < n; j++){
            internet[i][j] = 0;
         } 
      }
      
      //Read input into our internet graph
      for(i = 0; i < t; i++){
         int x, y, w;
         fscanf(fin, "%d %d %d", &x, &y, &w);
         internet[x][y] = w;
         internet[y][x] = w;
      }
      
      //We set the largest cat that can arrive at the LOLDEX to infinity, just to get things started.
      largestTube[0] = INF;
      
      //The following is a variation of Dijkstra's algorithm. At each iteration, we'll do the following:
         //1. Find the computer whose largestTube is greatest and who we have not yet marked visited
            //If there is no computer that matches these criteria, we break
         //2. Mark this computer visited
         //3. For each computer x attached to this computer, we update largestTube[x] by comparing its current value to the value obtained from sending it a cat from this computer.
            //The value itself is the minimum of this computer's largestTube and the width of the connection between this and x.
      for(i = 0; i < n; i++){
         int k = -1;
			int maximum = 0;
			
			//Find the unvisited computer with the largest tube width
			for(j = 0; j < n; j++){
				if(!visited[j] && largestTube[j] > maximum){
					k = j;
					maximum = largestTube[j];
				}
			}
			
			//Break if the computer was not found
			if(k == -1)
			   break;
			
			//Mark the computer visited
			visited[k] = 1;
			
			//Iterate through all computers connected to k
			for(j = 0; j < n; j++){
            //If j is connected to k and j is not visited
				if(internet[k][j] > 0 && !visited[j]){
               //The largest cat j can receive is either its current value or the value obtained by sending a cat from k
					largestTube[j] = max(largestTube[j], min(largestTube[k], internet[k][j]));
				}
         }
      }
      
      //The largest cat the LOLDEX can receive does not matter, so we set it to 0 to avoid printing it.
      largestTube[0] = 0;
      
      //Output answer
      printf("Series of tubes #%d:\n", cnt);
      for(i = 0; i < n; i++){
         if(largestTube[i] > 0)
            printf("Computer %d can receive up to a size %d LOLCAT.\n", i, largestTube[i]);
      }
      printf("\n");
         
      fscanf(fin, "%d %d", &n, &t);
      cnt++;
   }
      
   return 0;
}

//Returns the minimum of a and b
int min(int a, int b){
   if(a < b)
      return a;
   return b;
}

//Returns the maximum of a and b
int max(int a, int b){
   if(a > b)
      return a;
   return b;
}
