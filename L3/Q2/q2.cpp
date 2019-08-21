# include <bits/stdc++.h>
using namespace std;
/**
 * Defines the structure of a node in a linked list
 */
class Node
{
	public:
		int num;//!<Stores the cumulative xor	
		Node* next;//!<Stores the address of next node
		Node(int n)
		{
			num=n;
			next=NULL;
		}
};
/**
 * Defines the structure of a Linked list with insert operation
 */
class LinkedList
{
	public: 
		Node* root;//!<Defines the starting node of the list
		LinkedList()
		{	
			root=new Node(0);
		}
		/**
		 * returns the value stored in the node that is 'i' positions away from the root.
		 * @param i index of the node to be searched
		 */
		int getValue(int i)
		{
			Node* temp=root;
			while(i--)
			{
				temp=temp->next;
			}
			return temp->num;
		}
		/**
		 * Insert a node into the linked list.
		 * @param n the value of the cumulative xor to be stored in the node
		 */
		void insert(int n)
		{
			Node* temp=new Node(n);
			if(root==NULL)
				root=temp;
			else
			{
				Node* current=root;
				while(current->next)
				{
					current=current->next;
				}				
				current->next=temp;
			}
		}
};
/**
 * Print all possible triplets of the form (i,j,k) that satisfy the condition.
 * @param i 
 * @param k
 */
void printTriplet(int i, int k)
{
	for(int j=i+1; j<=k; j++)
		cout<<"("<<i<<","<<j<<","<<k<<")\n";
}
int main()
{
	clock_t t;
	t=clock();
	LinkedList dp;
	int n;
	int x;
	cin>>n;
	n++;
	for(int i=1; i<n; i++)
	{
		cin>>x;
		x=x^dp.getValue(i-1);
		dp.insert(x);
	}
	int flag=0;
	for(int i=0; i<n; i++)
	{
		for(int k=i; k<n; k++)
		{
			int xorItoK=dp.getValue(i)^dp.getValue(k);
			if(xorItoK==0)	
			{
				flag=1;
				printTriplet(i+1,k);
			}
		}
	}	
	if(!flag)
		cout<<"No possible triplets\n";
	t=clock()-t;
	double cpuTime=(double)t/CLOCKS_PER_SEC;	
	cout<<"CPU time: "<<cpuTime<<"\n";
	return 0;
}
