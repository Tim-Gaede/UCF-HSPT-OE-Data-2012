import java.util.*;
import java.io.*;
public class smell{
	public static void main(String[] args) throws IOException{
		Scanner br = new Scanner(System.in);
		int cases = br.nextInt();
		//loop over all the cases
		for(int i = 0;i<cases;i++){
			//read in the name
			String name = br.next();
			System.out.println("Name #"+(i+1)+":");
			System.out.println("Does " + name + " like the smell of adventure? Of course they do.");
			System.out.println();
		}
	}
}
