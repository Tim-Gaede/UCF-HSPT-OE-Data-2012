import java.util.*;
import java.io.*;

/*
 * The main difficulty of this problem is in parsing the input.
 * To do this, we're going to use the built-in java class, Scanner.
 * Scanner offers powerful functionality that we will exploit
 * to solve this problem.  In general though, using Scanner is
 * a good way to take in input from any problem.
 */

public class graphics {
	public static void main(String[] args) throws Exception {
		new graphics().run();
	}
	
	public void run() throws Exception {
		Scanner in = new Scanner(System.in);
		
		//We loop on the number of test cases.
		int numCases = in.nextInt();
		for(int curCase = 1; curCase <= numCases; curCase++) {
			
			//Each case starts with a board size
			int height = in.nextInt();
			int width = in.nextInt();
			//We'll initialize a char array as our board
			char[][] board = new char[height][width];
			//and fill it with blank spaces using the character literal ' '
			for(int y = 0; y < height; ++y) {
				Arrays.fill(board[y], ' ');
			}
			
			//the output also has a "mode", which we'll read in
			String mode = in.next();
			boolean paintOver = mode.equals("N");
			
			/*
			 * Now for the harder part; we need to read in the first part.
			 * We'll read in the first bit of the input, which I'll call
			 * the "token".  If the token is the word "END", then the program
			 * is done and we'll move on to output.  Otherwise, it's a
			 * number, and we need to read in the rest of the command.
			 */
			String token;
			do {
				
				token = in.next();
				if(!token.equals("END")) {
					
					//First, we'll convert the token to an integer, then
					//read in the rest of the command.
					int sr = Integer.parseInt(token);
					int sc = in.nextInt();
					int er = in.nextInt();
					int ec = in.nextInt();
					//Scanner has no simple way to read in a single character.
					//To do so, we read in a string and only use it's first character.
					char symbol = in.next().charAt(0);
					
					//Now that we have all the information for this command,
					//we execute it by filling in the portion of the board.
					for(int y = sr; y <= er; ++y) {
						for(int x = sc; x <= ec; ++x) {
							if(board[y][x] == ' ' || paintOver) {
								board[y][x] = symbol;
							}
						}
					}
					
				}
				
			} while(!token.equals("END"));

			/*
			 * Now we need to output the board after all the commands are executed.
			 * The output looks difficult, but we'll use a trick to make things
			 * simple: the mod operator.  The mod (%) operator gives us back the
			 * remainder of a division.  So 5 % 3 would be the remainder from
			 * 5 / 3, which is 2.  In this case, we'll use % 10 to get the one's
			 * digit of the row and column to output.
			 */
			System.out.printf("Canvas #%d%n", curCase);
			System.out.print(" ");
			for(int x = 0; x < width; ++x) {
				System.out.print(x % 10);
			}
			System.out.println();
			
			for(int y = 0; y < height; ++y) {
				System.out.print(y % 10);
				
				for(int x = 0; x < width; ++x) {
					System.out.print(board[y][x]);
				}
				
				System.out.println(y % 10);
			}
			//Lastly, we leave a blank space and we're done!
			System.out.println();
			
		}
	}
}
