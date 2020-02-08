import java.util.*;
class q2
{
	static int list[];
	static int minimumSegmentTree[];
	static int maximumSegmentTree[];
	static int sumSegmentTree[];
	static int aalsi[];
	public static void push(int temp,int theLeft,int theRight)
	{
		if(aalsi[temp]==0)
			return;
		if(theLeft!=theRight)
		{
			aalsi[2*temp]+=aalsi[temp];
			aalsi[2*temp+1]+=aalsi[temp];
			int theMiddle=(theLeft+theRight)/2;
			sumSegmentTree[2*temp]+=(theMiddle-theLeft+1)*aalsi[temp];
			sumSegmentTree[2*temp+1]+=(theRight-theMiddle)*aalsi[temp];
			minimumSegmentTree[2*temp]+=aalsi[temp];
			maximumSegmentTree[2*temp]+=aalsi[temp];
			minimumSegmentTree[2*temp+1]+=aalsi[temp];
			maximumSegmentTree[2*temp+1]+=aalsi[temp];
		}
		aalsi[temp]=0;
		return;
	}
	public static int query(int temp,int theLeft,int theRight,int left,int right,int type)
	{
		if(left>right)
		{
			if(type==1)
				return 10000;
			else if(type==2)
				return -10000;
			else
				return 0;
		}
		if(left==theLeft && right==theRight)
		{
			if(type==1)
				return minimumSegmentTree[temp];
			else if(type==2)
				return maximumSegmentTree[temp];
			else
				return sumSegmentTree[temp];
		}
		push(temp,theLeft,theRight);
		int theMiddle=(theLeft+theRight)/2;
		int q1=query(2*temp, theLeft, theMiddle, left, Math.min(right,theMiddle), type);
		int q2=query(2*temp+1, theMiddle+1, theRight, Math.max(left,theMiddle+1), right, type);
		if(type==1)
			return Math.min(q1,q2);
		else if(type==2)
			return Math.max(q1,q2);
		else
			return q1+q2;
	}
	public static void update(int temp,int theLeft,int theRight,int left,int right)
	{
		if(left>right)
			return;
		if(left==theLeft && right==theRight)
		{
			aalsi[temp]+=4;
			sumSegmentTree[temp]+=(theRight-theLeft+1)*4;
			minimumSegmentTree[temp]+=4;
			maximumSegmentTree[temp]+=4;
			return;
		}
		push(temp,theLeft,theRight);
		int theMiddle=(theLeft+theRight)/2;
		update(2*temp,theLeft,theMiddle,left,Math.min(right,theMiddle));
		update(2*temp+1,theMiddle+1,theRight,Math.max(theMiddle+1,left),right);
		minimumSegmentTree[temp]=Math.min(minimumSegmentTree[2*temp],minimumSegmentTree[2*temp+1]);
		maximumSegmentTree[temp]=Math.max(maximumSegmentTree[2*temp],maximumSegmentTree[2*temp+1]);
		sumSegmentTree[temp]=sumSegmentTree[2*temp]+sumSegmentTree[2*temp+1];
		return;
	}
	public static void makeSegmentTree(int temp,int theLeft,int theRight)
	{
		if(theLeft==theRight)
		{
			minimumSegmentTree[temp]=list[theLeft];
			maximumSegmentTree[temp]=list[theLeft];
			sumSegmentTree[temp]=list[theLeft];
			return;
		}
		int theMiddle=(theLeft+theRight)/2;
		makeSegmentTree(2*temp,theLeft,theMiddle);
		makeSegmentTree(2*temp+1,theMiddle+1,theRight);
		minimumSegmentTree[temp]=Math.min(minimumSegmentTree[2*temp],minimumSegmentTree[2*temp+1]);
		maximumSegmentTree[temp]=Math.max(maximumSegmentTree[2*temp],maximumSegmentTree[2*temp+1]);
		sumSegmentTree[temp]=sumSegmentTree[2*temp]+sumSegmentTree[2*temp+1];
		return;
	}
	public static void main(String args[])
	{
		Scanner input = new Scanner(System.in);
		int n = input.nextInt();
		list = new int[n];
		for(int i=0;i<n;i++)
			list[i]=input.nextInt();
		minimumSegmentTree=new int[5*n];
		maximumSegmentTree=new int[5*n];
		sumSegmentTree=new int[5*n];
		aalsi = new int[5*n];
		makeSegmentTree(1,0,n-1);
		int choice,left=0,right=0;
		do
		{
			System.out.println("\n1: Find minimum value");
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
			if((choice>0 && choice<5) && (left>right || left<0 || right>=n))
			{
				System.out.println("Invalid Index");
				continue;
			}
			switch(choice)
			{
				case 1:
				{	
					long startTime = System.nanoTime();
					System.out.print("Minimum is : ");
					System.out.println(query(1,0,n-1,left,right,1));
					long endTime = System.nanoTime();
					long duration = endTime - startTime;
					System.out.println("The execution time: "+duration);
					break;
				}
				case 2:
				{
					long startTime = System.nanoTime();
					System.out.print("Maximum is : ");
					System.out.println(query(1,0,n-1,left,right,2));
					long endTime = System.nanoTime();
					long duration = endTime - startTime;
					System.out.println("The execution time: "+duration);
					break;
				}
				case 3:
				{	
					long startTime = System.nanoTime();
					System.out.print("Sum is : ");
					System.out.println(query(1,0,n-1,left,right,3));
					long endTime = System.nanoTime();
					long duration = endTime - startTime;
					System.out.println("The execution time: "+duration);
					break;
				}
				case 4:
				{
					long startTime = System.nanoTime();
					update(1,0,n-1,left,right);
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
