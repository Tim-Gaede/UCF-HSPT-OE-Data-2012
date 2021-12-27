import java.util.*;
import java.io.*;
public class tubes
{
	public tubes() throws IOException
	{
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		int t = in.nextInt();
		int tubeSet = 1;
		//since n is gaurenteed to be between 1 and 50, I will use it as a terminating condition
		while(n!=0)
		{
			System.out.printf("Series of tubes #%d:\n",tubeSet++);
			
			//read in the input and format it into an adjacency matrix
			int[][] adjmat = new int[n][n];
			
			//set all nodes to unreachable
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					adjmat[i][j]=-1;
			for(int i = 0; i < t; i++)
			{
				int cpu1 = in.nextInt();
				int cpu2 = in.nextInt();
				int tubeSize = in.nextInt();
				
				adjmat[cpu1][cpu2]=tubeSize;
				adjmat[cpu2][cpu1]=tubeSize;
			}
			
			int[] answerArray = new int[n];
			//set all the nodes in the answer array to "unreachable"
			for(int i = 0; i < n; i++)
				answerArray[i]=-1;
			
			//100 is set as the size because the largest tube is one of size 50, just needs to be a number bigger
			dfs(adjmat,0,100,answerArray);
			
			for(int i = 1; i < n; i++)
				if(answerArray[i]!=-1)
					System.out.printf("Computer %d can receive up to a size %d LOLCAT.\n",i,answerArray[i]);
			
			System.out.println();
			n=in.nextInt();
			t=in.nextInt();
		}
	}
	public void dfs(int[][] adjmat, int index, int curSize, int[] answerStorage)
	{
		for(int i = 0; i < adjmat.length; i++)
		{
			if(index==i)
				continue;
			if(adjmat[index][i]>answerStorage[i] && curSize>answerStorage[i])
			{
				if(curSize>=adjmat[index][i])
				{
					answerStorage[i]=adjmat[index][i];
					dfs(adjmat,i,adjmat[index][i],answerStorage);
				}
				else
				{
					answerStorage[i]=curSize;
					dfs(adjmat,i,curSize,answerStorage);
				}
			}
		}
	}
	public static void main(String[] args) throws IOException
	{
		new tubes();
	}
}
