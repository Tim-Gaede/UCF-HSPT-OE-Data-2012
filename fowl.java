/*********************************
 Java Solution
 Problem Fowl
 *********************************/

import java.io.*;
import java.util.*;

public class fowl {
	public static void main(String[] Args)throws IOException{
		
		//Scanner for reading in the file
		Scanner sc = new Scanner(System.in);
		
		//number of test cases that will be read in
		int num_of_cases = sc.nextInt();
		
		//a for loop to loop through all the cases
		for(int count = 1; count <= num_of_cases; count++){
			
			//integers a, b, and c store the three numbers for each case
			int a = sc.nextInt();
			int b = sc.nextInt();
			int c = sc.nextInt();
			
			//check all three possible cases for a right triangle
			if(a >= b && a >= c)
				if(a * a == (b * b) + (c * c))
					System.out.println("Target #" + count + ": YES");
				else
					System.out.println("Target #" + count + ": NO");
			else if(b >= a && b >= c)
				if(b * b == (a * a) + (c * c))
					System.out.println("Target #" + count + ": YES");
				else
					System.out.println("Target #" + count + ": NO");
			else
				if(c * c == (a * a) + (b * b))
					System.out.println("Target #" + count + ": YES");
				else
					System.out.println("Target #" + count + ": NO");
		}
	}
}
