
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Bowl and dimensions
int bowl[64][128][128];
int h, w, b;


// This function transforms the contents of the bowl to indicate the "degree"
// of each cube.  The degree is simply a count of how many other cubes are
// connected to that cube (i.e.: if this cube has a piece of pasta, how many
// of the adjacent cubes also have a piece of pasta).  As the problem
// specifies, we only count pieces of pasta that share cube faces (not edges
// or points) as adjacent
void findDegree()
{
   int   i, j, k;
   int   degree;

   // Iterate over each cell of the bowl
   for (i = 1; i <= h; i++)
   {
      for (j = 1; j <= w; j++)
      {
         for (k = 1; k <= b; k++)
         {
            // See if this is pasta or broth
            if (bowl[i][j][k] > 0)
            {
               // Start with a degree of zero
               degree = 0;

               // Look up
               if (bowl[i-1][j][k] > 0)
                  degree++;

               // Look down
               if (bowl[i+1][j][k] > 0)
                  degree++;

               // Look left
               if (bowl[i][j-1][k] > 0)
                  degree++;

               // Look right
               if (bowl[i][j+1][k] > 0)
                  degree++;

               // Look back
               if (bowl[i][j][k-1] > 0)
                  degree++;

               // Look forward
               if (bowl[i][j][k+1] > 0)
                  degree++;

               // Record the cell's degree.  Note that the degree will be zero
               // if it is not connected to anything else, and the cell will
               // effectively be lost.  This is OK, as the cell won't be a
               // factor in the problem if this is the case
               bowl[i][j][k] = degree;
            }
         }
      }
   }
}


// This function scans the bowl looking for elbow macaroni.  It prints
// a message any time it finds one (or a single message indicating it couldn't
// find any)
void findElbows()
{
   int   i, j, k;
   int   found;
   int   x[2], y[2], z[2];
   int   totalFound;

   // Start with no elbows found
   totalFound = 0;

   // Iterate over each cell of the bowl
   for (i = 1; i <= h; i++)
   {
      for (j = 1; j <= w; j++)
      {
         for (k = 1; k <= b; k++)
         {
            // See if this is a potential elbow
            if (bowl[i][j][k] == 2)
            {
               // Now find the coordinates of the two connected cubes
               // Look up
               found = 0;
               if (bowl[i-1][j][k] > 0)
               {
                  x[found] = i-1;
                  y[found] = j;
                  z[found] = k;
                  found++;
               }

               // Look down
               if (bowl[i+1][j][k] > 0)
               {
                  x[found] = i+1;
                  y[found] = j;
                  z[found] = k;
                  found++;
               }

               // Look left
               if (bowl[i][j-1][k] > 0)
               {
                  x[found] = i;
                  y[found] = j-1;
                  z[found] = k;
                  found++;
               }

               // Look right
               if (bowl[i][j+1][k] > 0)
               {
                  x[found] = i;
                  y[found] = j+1;
                  z[found] = k;
                  found++;
               }

               // Look back
               if (bowl[i][j][k-1] > 0)
               {
                  x[found] = i;
                  y[found] = j;
                  z[found] = k-1;
                  found++;
               }

               // Look forward
               if (bowl[i][j][k+1] > 0)
               {
                  x[found] = i;
                  y[found] = j;
                  z[found] = k+1;
                  found++;
               }

               // Now, make sure the two connected cubes are both degree 1.
               // If so, this means that no cubes other than the two we
               // found are connected to the potential elbow
               if ((bowl[x[0]][y[0]][z[0]] == 1) &&
                   (bowl[x[1]][y[1]][z[1]] == 1))
               {
                  // Finally, make sure the two connected cubes are not
                  // on opposite sides of the elbow (otherwise, we have ziti
                  // and not elbow macaroni)
                  if ((abs(x[0] - x[1]) < 2) &&
                      (abs(y[0] - y[1]) < 2) &&
                      (abs(z[0] - z[1]) < 2))
                  {
                     // Found an elbow, print it out!
                     printf("Elbow macaroni found at (%d,%d,%d). Zap it!\n",
                        i, j, k);

                     // Count it
                     totalFound++;
                  }   
               }
            }
         }
      }
   }

   // If we didn't find any, print a message
   if (totalFound == 0)
      printf("No elbow macaroni found. What are they hiding now?\n");
}


// This function just prints the current state of the bowl.  Useful for
// debugging
void printBowl()
{
   int  i, j, k;

   for (i = 1; i <= h; i++)
   {
      for (j = 1; j <= w; j++)
      {
         for (k = 1; k <= b; k++)
         {
            printf("%4d", bowl[i][j][k]);
         }

         printf("\n");
      }

      printf("\n");
   }
}


int main(void)
{
   FILE *   fp;
   char     line[128];
   int      numBowls;
   int      bowlNum;
   int      i, j, k;


   // Standard in
   fp = stdin;

   // Read the number of bowls
   fgets(line, sizeof(line), fp);
   sscanf(line, "%d\n", &numBowls);

   // Process each bowl
   for (bowlNum = 1; bowlNum <= numBowls; bowlNum++)
   {
      // Clear the bowl
      memset(bowl, 0, sizeof(bowl));

      // Read the dimensions
      fgets(line, sizeof(line), fp);
      sscanf(line, "%d %d %d\n", &h, &w, &b);

      // Read in each row of the bowl
      for (i = 1; i <= h; i++)
      {
         for (j = 1; j <= w; j++)
         {
            // Read the line
            fgets(line, sizeof(line), fp);

            // Store the line as 0 for 'O' or 100 for '@' (we'll process
            // these values into something more meaningful in a bit).  Note
            // that we're starting at 1 instead of zero.  This makes it
            // easier to scan through the stuff in the bowl later without
            // having to worry about looking outside the bounds of the array.
            for (k = 1; k <= b; k++)
            {
               if (line[k-1] == 'O')
                  bowl[i][j][k] = 0;
               else
                  bowl[i][j][k] = 100;
            }
         }
      }

      // Print the header for the bowl
      printf("Bowl #%d:\n", bowlNum);

      // Now examine the bowl's contents as if it were a disconnected
      // graph, and determine the "degree" of each node.  That is, examine
      // each "cube" in the bowl and figure out how many other "cubes" are
      // connected to it
      findDegree();

      // Now, scan the bowl for 2's.  A degree of two means there are exactly
      // two cubes connected to it, so that cube is a potential elbow. If both
      // of those adjacent cubes are degree 1 and they're not on opposite
      // sides of the potential elbow, we definitely have an elbow!
      findElbows();

      // Finish with a blank line
      printf("\n");
   }

   // Close the file
   fclose(fp);
}
