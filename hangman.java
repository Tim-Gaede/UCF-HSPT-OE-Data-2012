import java.util.*;
import java.io.*;

public class hangman {
	public static void main(String[] args) throws IOException {
	
		//Initialize the scanner
		Scanner in = new Scanner(System.in);
		
		//Read in the number of games to be checked
		int T = in.nextInt();
		
		//Loop through each game
		for (int t=0; t<T; t++) {
		
			//Input the starting height
			int N = in.nextInt();
			
			//Input the key
			String key = in.next();
			
			//Input the guesses
			String guesses = in.next();

			//Initialize variables			
			int uniqueChars = 0; //The number of unique characters in the key
			boolean[] hasChar = new boolean['z'-'a'+1]; //If the character exists in the key (note: the quantity of each letter does not matter)
			
			//Loop through the key, and set the correct values for uniqueChars and hasChar
			for (int k=0; k<key.length(); k++)
				if (!hasChar[key.charAt(k)-'a']) { //If the character has not been seen yet
					hasChar[key.charAt(k)-'a'] = true; //It has now been seen; it exists in the key
					uniqueChars++; //This is another unique character
				}
			
			//Loop through each letter of guess (while there are still characters to guess, and there 
			// are more needed to be guessed, and he is not in the lava)
			for (int g=0; g<guesses.length() && uniqueChars > 0 && N > 0; g++) {
				if (!hasChar[guesses.charAt(g)-'a']) //If the character does not exist in the key
					N--; //Lower poor Ali's height by 1
				else { //If the chracter does exist in the key
					uniqueChars--; //There is now one less unique character needed to be guessed
					hasChar[guesses.charAt(g)-'a'] = false; //But all occurances of that character are now gone from the key
				}
			}
			
			if (N > 0) //If Ali is done, and is above the lava, YAY!
				System.out.printf("Lava pit #%d: Ali survives!\n",t+1);
			else //If he is in or below the lava, poor Ali, I guess he won't be coming back next year
				System.out.printf("Lava pit #%d: Poor Ali.\n",t+1);
			
		}
	}
}
