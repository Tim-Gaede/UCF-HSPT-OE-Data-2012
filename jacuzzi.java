/* JACUZZI
 * 
 * Determine if a given set of sides can be used to build a jacuzzi (polygon).
 * This is only possible if the largest side is smaller than all other sides combined.
 */

import java.io.*;
import java.util.*;

public class jacuzzi {
	public static void main (String[] args) throws Exception {
		Scanner in = new Scanner(System.in);
		
		int numCases = in.nextInt();			//The number of cases in the input file
		
		for (int z=1; z <= numCases; z++) {
			int numSides = in.nextInt();		//The number of sides for this case
			
			int[] sides = new int[numSides];	//The sides to consider
			for (int i=0; i<numSides; i++)
				sides[i] = in.nextInt();
			
			//Sort the sides - this way we guarantee the largest side is at the end
			Arrays.sort(sides);
			
			//Find the sum of all the sides except the largest
			int sum = 0;
			for (int i=0; i<numSides-1; i++)
				sum += sides[i];
			
			//Output the jacuzzi number
			System.out.print("Jacuzzi #" + z + ": ");
			
			//If the largest side is smaller than the sum of the others, it's possible to build the jacuzzi/polygon
			if (sum > sides[numSides-1])
				System.out.println("YES");
			
			//Otherwise it's unbuildable
			else
				System.out.println("NO");
		}
	}
}
