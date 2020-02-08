import java.util.*;
class BruteForce
{
	public static void main(String args[])
	{
		Scanner input=new Scanner(System.in);
		int size = input.nextInt();
		int list[]=new int [size];
		for(int i=0;i<size;i++)
			list[i]=input.nextInt();
		int choice,left=0,right=0;
		do
		{
			System.out.println("1: Find minimum value");
			System.out.println("2: Find maximum value");
			System.out.println("3: Find sum");
			System.out.println("4: Update by adding 4");
			System.out.println("5: Exit");
			choice=input.nextInt();
			if(choice>0 && choice<5)
			{
				System.out.println("Enter range");
				System.out.print("Index 1 : ");
				left=input.nextInt();
				System.out.print("Index 2 : ");
				right=input.nextInt();
			}
			if((choice>0 && choice<5) && (left>right || left<0 || right>=size))
			{
				System.out.println("Invalid Index");
				continue;
			}
			switch(choice)
			{
				case 1:
				{
					long startTime = System.nanoTime();
					int minimum=10000;
					for(int i = left;i <= right; i++)
						minimum=Math.min(minimum,list[i]);
					System.out.println("Minimum is : "+minimum);
					long endTime = System.nanoTime();
					long duration = endTime - startTime;
					System.out.println("The execution time: "+duration);
					break;
				}
				case 2:
				{
					long startTime = System.nanoTime();
					int maximum=-10000;
					for(int i=left;i<=right;i++)
						maximum=Math.max(maximum,list[i]);
					System.out.println("Maximum is : "+maximum);
					long endTime = System.nanoTime();
					long duration = endTime - startTime;
					System.out.println("The execution time: "+duration);
					break;
				}
				case 3:
				{
					long startTime = System.nanoTime();
					int sum=0;
					for(int i=left;i<=right;i++)
						sum+=list[i];
					System.out.println("Sum is : "+sum);
					long endTime = System.nanoTime();
					long duration = endTime - startTime;
					System.out.println("The execution time: "+duration);
					break;
				}
				case 4:
				{
					long startTime = System.nanoTime();
					for(int i=left;i<=right;i++)
						list[i]+=4;
					long endTime = System.nanoTime();
					long duration = endTime - startTime;
					System.out.println("The execution time: "+duration);
					break;
				}
				default:
				break;
			}
		}
		while(choice!=5);
		return;
	}
}
