// Arup Guha
// 4/21/2011
// Solution for 2011 UCF High School Online Contest problem: Elbow 

import java.io.*;
import java.util.*;

// Class just stores one grid square.
class square implements Comparable<square> {

	final public static int DIM = 3;
	public int[] coord;
	
	// Creates a square index by DIM dimensions.
	public square(int[] point) {
		
		coord = new int[DIM];
		
		// Fill in coord with each coordinate given in point. If
		// point doesn't have a corresponding coordinate, store 0.
		for (int i=0; i<DIM; i++)
			if (i < point.length)
				coord[i] = point[i];
			else
				coord[i] = 0;
	}
	
	// Implements the ordering specified in the assignment.
	public int compareTo(square other) {

		// Find the first mismatching coordinate.
		int i = 0;
		while (i < DIM && this.coord[i] == other.coord[i])
			i++;
			
		// Equal case.
		if (i == DIM)
			return 0;
			
		// The difference in this coordinate will suffice.
		else
			return this.coord[i] - other.coord[i];
	}
	
	// Returns a new square object, the same as this, except with 
	// a change of offset in the dimension passed in. For example,
	// square(2, 8, 1).add(1, -3) would return square(2, 5, 1).
	public square add(int dimension, int offset) {
		
		int[] copy = new int[DIM];
		
		// Copy the original values.
		for (int i=0; i<DIM; i++)
			copy[i] = coord[i];
			
		// Change this one dimension by offset.
		copy[dimension] += offset;
		return new square(copy);
		
	}
	
	// Returns the distance squared between this and other.
	public int distSq(square other) {
		
		int sumSq = 0;
		
		for (int i=0; i<DIM; i++)
			sumSq += (this.coord[i] - other.coord[i])*(this.coord[i] - other.coord[i]);
		
		return sumSq;
	}
	
	public String toString() {
		String s = "Elbow macaroni found at (";
		
		// Concatenate each coordinate.
		// This is horrible style, but the output is one-based, but I made all
		// my calculations zero based, which was easier to code. So, I just add
		// one to each coordinate.
		for (int i=0; i<DIM-1; i++)
			s = s + (coord[i]+1) + ",";
		s = s + (coord[DIM-1]+1);
		
		s = s + "). Zap it!";
		
		return s;
	}
}

class shape {
	
	public ArrayList<square> allSquares;
	
	// To start a shape, we start it with a single square.
	public shape() {
		allSquares = new ArrayList<square>();
	}

	// Pre-condition: s is not part of the current object.	
	public void addSquare(square s) {
		allSquares.add(s);
	}
	
	// Returns true iff s is contained in this object.
	public boolean inShape(square s) {
		for (square thisone: allSquares)
			if (thisone.compareTo(s) == 0)
				return true;
		return false;
	}
	
	// Returns true iff this is an elbow.
	public boolean isElbow() {
		
		// All elbows have three squares.
		if (allSquares.size() != 3)
			return false;
			
		int numOne = 0, numTwo = 0;
		
		for (int i=0; i<3; i++) {
			for (int j=i+1; j<3; j++) {
				
				// Calculate the distance between these two pieces.
				int dist = allSquares.get(i).distSq(allSquares.get(j));
				if (dist == 1)
					numOne++;
				else if (dist == 2)
					numTwo++;
					
				// If two pieces are farther apart that sqrt(2), the shape 
				// isn't an elbow.
				else 
					return false;
			}
		}
		
		// Elbow requirements.
		if (numOne == 2 && numTwo == 1)
			return true;
			
		return false;
	}
	
	// Pre-condition: This must be an elbow!!!
	public square findMidElbow() {
		
		// Testing piece i to be the middle of the elbow.
		for (int i=0; i<3; i++) {
			
			int sum = 0;
			for (int j=0; j<3; j++) {
				
				// Calculate the distance between these two pieces.
				sum += allSquares.get(i).distSq(allSquares.get(j));
				
			}
			
			// The middle piece will achieve a sum of 2 here. Other pieces won't.
			if (sum == 2)
				return allSquares.get(i);
		}
		
		// Should never get here, but the compiler complains without it.
		return allSquares.get(0);
	}
		
	// checks to see if this shape is empty.
	public boolean isEmpty() {
		return allSquares.size() == 0;
	}
	
}
public class elbow {
	
	public int[] size;
	public char[][][] box;
	public boolean[][][] used;
	public ArrayList<shape> pieces;
	
	public elbow(int h, int w, int b) {
		
		// Set up the dimensions and allocate space.
		size = new int[square.DIM];
		size[0] = h;
		size[1] = w;
		size[2] = b;
		box = new char[h][w][b];
		used = new boolean[h][w][b];
		
		// No square has been searched yet.
		for (int i=0; i<h; i++)
			for (int j=0; j<w; j++)
				for (int k=0; k<b; k++)
					used[i][j][k] = false;
					
		pieces = new ArrayList<shape>();
	}
	
	public void readBox(Scanner fin) {
		
		// Go through each level of the box.
		for (int i=0; i<size[0]; i++) {
			
			// Go through each row.
			for (int j=0; j<size[1]; j++) {
				
				// Set up each character in the box.
				String temp = fin.next();
				for (int k=0; k<size[2]; k++)
					box[i][j][k] = temp.charAt(k);
			}
		}
	}
	
	// Pre-condition: Must be called AFTER fillShapes() has been called.
	public int solve() {
		
		ArrayList<square> elbows = new ArrayList<square>();
		
		// Go through our original list and add the middle square of
		// each elbow in our list.
		for (shape s: pieces)
			if (s.isElbow())
				elbows.add(s.findMidElbow());
			
		// Indicates that this 
		if (elbows.size() == 0)
			return 0;
				
		Collections.sort(elbows);
		
		// Output the results for this case.
		for (int i=0; i<elbows.size(); i++)
			System.out.println(elbows.get(i));
			
		// Return the number of elbows.
		return elbows.size();
	}
	
	public void fillShapes() {
		
		int i, j, k;
		
		// Run through the whole grid, marking each shape.
		for (i=0; i<size[0]; i++) {
			for (j=0; j<size[1]; j++) {
				for (k=0; k<size[2]; k++) {
					
					// We can start a new piece with this square
					if (!used[i][j][k] && box[i][j][k] == '@') {
						
						// Fill in this shape.
						int[] xyz = {i, j, k};
						square start = new square(xyz);
						shape my_shape = new shape();
						floodfill(my_shape, start);
						
						// Add it to our list.
						if (!my_shape.isEmpty()) {	 
							pieces.add(my_shape);
						}
						
					}
				}
			}
		}
		
	}
	
	// Returns true if point is inbounds for this object.
	public boolean inbounds(int[] point) {
		
		// Prevent illegal comparisons.
		if (point.length != size.length)
			return false;
			
		int i;
		
		// See if any coordinate is out of bounds.
		for (i=0; i<point.length; i++)
			if (point[i] < 0 || point[i] >= size[i])
				return false;
				
		return true;
	}
	
	// Returns true iff s is a valid square to explore from to
	// find a new piece.
	public boolean valid(square s) {

		// Stop if this is out of bounds.
		if (!inbounds(s.coord)) return false;
	
		int x = s.coord[0];
		int y = s.coord[1];
		int z = s.coord[2];
		
		// Stop if this piece is in a previous shape.
		if (used[x][y][z]) return false;
		
		// Stop if this isn't partof a piece. 
		if (box[x][y][z] != '@') return false;
		
		return true;
	}
	
	// Pre-condition: current is NOT yet part of this_shape.
	// Post-conditions: If the floodfill is successful, null is returned. If it
	//                  is stopped short to cut off the recursion, the square which
	//                  wasn't filled last is returned.
	public void floodfill(shape this_shape, square current) {
		
		// Cut off bad calls.
		if (!valid(current))
			return;
		
		// Start my queue of squares that need to be explored.
		Queue<square> myqueue = new LinkedList<square>();
		myqueue.offer(current);
		
		// Continue until no more squares need to be explored.
		while (!myqueue.isEmpty()) {
		
			// Adjust the queue.
			square next = myqueue.poll();
			int x = next.coord[0];
			int y = next.coord[1];
			int z = next.coord[2];
			
			// We can add this square into our shape.
			used[x][y][z] = true;
			this_shape.addSquare(next);
		
			// Loop through the six adjacent squares to continue the floodfill.
			for (int i=0; i<square.DIM; i++) {
				
				// Move in the positive direction in each dimension from
				// the current square. If valid, mark as used.
				square moveTo = next.add(i, 1);
				if (valid(moveTo)) {
					myqueue.offer(moveTo);
					x = moveTo.coord[0];
					y = moveTo.coord[1];
					z = moveTo.coord[2];
					used[x][y][z] = true; 
				
				}
				
				// Do the same in the negative directions.
				moveTo = next.add(i, -1);
				if (valid(moveTo)) {
					myqueue.offer(moveTo);
					x = moveTo.coord[0];
					y = moveTo.coord[1];
					z = moveTo.coord[2];
					used[x][y][z] = true; 
				}
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		
		Scanner fin = new Scanner(System.in);
		
		int numCases = fin.nextInt();
		
		// Go through each case.
		for (int i=1; i<=numCases; i++) {
				
			// Read in the dimensions.
			int x, y, z;
			x = fin.nextInt();
			y = fin.nextInt();
			z = fin.nextInt();
			
			// Get everything set up.
			elbow my_elbow = new elbow(x, y, z);
			my_elbow.readBox(fin);
			my_elbow.fillShapes();
			
			// Case header.
			System.out.println("Bowl #"+i+":");
			int solution = my_elbow.solve();
			
			// If there are no elbows, we have a special line of output.
			if (solution == 0)
				System.out.println("No elbow macaroni found. What are they hiding now?");
				
			// Blank line between cases.
			System.out.println();
		}
		
		fin.close();
	}	
}
