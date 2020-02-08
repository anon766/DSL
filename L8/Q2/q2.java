import java.io.*;
import java.util.*;
class q2
{
	static HashSet<String> listOfWords=new HashSet<String>();
	static HashSet<String> solution=new HashSet<String>();
	static int noOfWords;
	int random1;
	int random2;
	int random3;
	public static void main(String args[])throws Exception
	{
		DataInputStream input=new DataInputStream(System.in);
		System.out.print("Enter word: ");
		String temporary=input.readLine();
		for(int i=0;i<temporary.length();i++)
		{
			for(int j=i+1;j<temporary.length();j++)
			{
			if((int)temporary.charAt(i)>(int)temporary.charAt(j))
			{
				temporary=temporary.substring(0,i)+temporary.charAt(j)+temporary.substring(i+1,j)+temporary.charAt(i)+temporary.substring(j+1,temporary.length());
			}
			}
		}
		File fp=new File("dictionary.txt");
		Scanner z=new Scanner(fp);
		while(z.hasNextLine())
		{
			String curr=z.nextLine();
			listOfWords.add(curr);
		}
		for(int i=temporary.length();i>3;i--)
		{
			noOfWords=0;
			solution.clear();
			System.out.println("Length: "+i);
			createPnC(temporary,i,"");
			System.out.println();
			System.out.println("Count: "+noOfWords);
		}
		return;
	}
	public void randomFunc()
	{
		int random4;
		float random5;
	}
	private int randomFunc1()
	{
		int random6;
		randomFunc();
		return 1;
	}
	public static void createPnC(String temporary,int noOfLetters,String temp)
	{
		if(noOfLetters==0)
		{
			if(listOfWords.contains(temp) && !solution.contains(temp))
			{
				System.out.print(temp+" ");
				noOfWords++;
				solution.add(temp);
			}
			return;
		}
		for(int i=0;i<temporary.length();i++)
		{
			String x=temporary.substring(0,i)+temporary.substring(i+1,temporary.length());
			createPnC(x,noOfLetters-1,temp+temporary.charAt(i));
		}
		return;
	}
	public boolean isTrue()
	{
		int i;
		int j;
		System.out.println("Not found");
		return true;
	}
}
