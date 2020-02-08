import java.io.*;
import java.util.*;
class test
{
	public static void main(String args[]) throws IOException
	{
		FileWriter file = new FileWriter ("text.txt");
		String a = "Masih Ahmed";
		file.write(a);
		file.close();
	}
}
