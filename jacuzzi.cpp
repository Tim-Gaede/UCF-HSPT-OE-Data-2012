/*
Problem: JACUZZI
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// This function solves the problem with sorting
bool solveOtherWay(int * sides, int N)
{
   // First we sort the data, I will use selection sort
   // since this sorting method is the easiest to code
   // for me. Another approach would be to use the stl
   // google "c++ stl" for ways to sort arrays in c++
   // Selection sort works by finding the smallest element
   // and swapping it with that position in the array
   for (int i=0; i<N; i++)
      for (int j=i+1; j<N; j++)
         if (sides[j] < sides[i])
         {
            // Swap the two sides
            int tmp = sides[i];
            sides[i] = sides[j];
            sides[j] = tmp;
         }

   // Now we simply sum everything but the largest element
   int sum = 0;
   for (int i=0; i<(N-1); i++)
      sum += sides[i];
   
   // For the result we only care if the sum is greater than the
   // longest side of the polygon
   return (sides[N-1] < sum);
}

// This is the cooler way to solve this problem without sorting
bool solveWayCool(int * sides, int N)
{
   // First we sum all the sides, we also keep trace of the longest one
   int longest = 0;
   int sum = 0;
   for (int i=0; i<N; i++)
   {
      sum += sides[i];
      if (sides[i] > longest)
         longest = sides[i];
   }

   // Now we subtract out the longest side from the sum of sides
   sum -= longest;

   // Now that we have the sum of all the sides except the longest
   // we can determine if we can make a polygon from the sides
   return (longest < sum);
}

// Picks which way to solve the problem and return the result
bool solve(int * sides, int N)
{
   // There are two ways to solve this problem that are noteworthy
   // I will present both of them, just pick which way works best 
   // for you or makes the most sense.

   // The basic idea for this problem is that we are trying to find
   // if the sides of the jacuzzi can make a polygon. We are also only
   // interested in polygons that can hold water which means we don't 
   // want to include degenerate polygons (degenerate polygons are polygons
   // that don't have any area) If you remember from geometry class
   // given a number of sides you can form a polygon if and only if
   // the length of the longest side is less than the sum of the other
   // side in the polygon. Both these solutions use this concept but one
   // uses a clever trick to get out of sorting the sides of the polygon

   bool awesome = true;
   if (awesome)
      return solveWayCool(sides, N);
   return solveOtherWay(sides, N);
}

// Main handles the io 
int main()
{
   FILE * fptr = stdin;
   int sides[100];
   
   // Read in the number of test cases
   int T; fscanf(fptr, "%d", &T);

   // Loop through each test case in the input
   for (int t=1; t<=T; t++)
   {
      // I'm old school and use the c way of reading input
      int N; fscanf(fptr, "%d", &N);

      // Read in the array of jacuzzi sides using pointer math
      // when reading in arrays it works better to send the 
      // modified pointer instead of &sides[i]
      for (int i=0; i<N; i++)
         fscanf(fptr, "%d", sides+i);

      // Print out the output and solve the problem
      printf("Jacuzzi #%d: ", t);
      if (solve(sides, N))
         printf("YES");
      else
         printf("NO");
      printf("\n");
   }

   return 0;
}
