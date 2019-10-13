#include<bits/stdc++.h>
using namespace std;
class  Node
{
	public:
	int val;
	Node* next;
	Node(int a)
	{
		val=a;
		next=NULL;
	}
};
Node* adjacencyList[100];
int dp[100][100];
bool used[100];
Node* resultStore;
int src;
bool isCycle;

void insertResult(int );
void searchDFS(int ,int );
void insert(int ,int );
int main()
{
	char v1,v2;
	string temp;
	int ch;
	src=-1;
	fstream file;
	file.open("L6_Q1_sample_input.txt");
	if(!file.is_open())
		cout<<"Unable to open input file."<<endl;
	do
	{
		cout<<"\t\t\tMENU\n\n";
		cout<<"1. Insert Edges"<<endl;
		cout<<"2. BFS traversal"<<endl;
		cout<<"3. DFS traversal"<<endl;
		cout<<"4. Cycle finding in the graph"<<endl;
		cout<<"5. Calculate dmt of the graph"<<endl;
		cout<<"6. Exit"<<endl;
		cout<<"Enter choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
			while(getline(file,temp))
			{
				v1=temp[0];
				v2=temp[2];
				insert((int)v1-(int)'A',(int)v2-(int)'A');
				insert((int)v2-(int)'A',(int)v1-(int)'A');
				if(src==-1)
					src=(int)v1-(int)'A';
			}
			break;
			case 2:
			{
				if(src==-1)
					break;
				resultStore=NULL;
				memset(used,false,sizeof(used));
				insertResult(src);
				used[src]=true;
				while(resultStore!=NULL)
				{
					int v=resultStore->val;
					cout<<(char)(v+(int)'A')<<" ";	
					Node* x=adjacencyList[v];
					while(x!=NULL)
					{
						if(!used[x->val])
						{
							insertResult(x->val);
							used[x->val]=true;
						}
						x=x->next;
					}
					resultStore=resultStore->next;
				}
				cout<<endl;
				break;
			}
			case 3:
			{
				if(src==-1)
					break;
				resultStore=NULL;
				memset(used,false,sizeof(used));
				searchDFS(src,-1);
				Node* x=resultStore;
				while(x!=NULL)
				{
					cout<<(char)(x->val+(int)'A')<<" ";
					x=x->next;
				}
				cout<<endl;
				break;
			}
			case 4:
			{
				if(src==-1)
					break;
				resultStore=NULL;
				memset(used,false,sizeof(used));
				isCycle=false;
				searchDFS(src,-1);
				if(isCycle)
					cout<<"Yes"<<endl;
				else
					cout<<"No"<<endl;
				break;
			}
			case 5:
			{
				if(src==-1)
					break;
				for(int i=0;i<100;i++)
					for(int j=0;j<100;j++)
						dp[i][j]=1000;
				for(int i=0;i<100;i++)
				{
					Node* x=adjacencyList[i];
					while(x!=NULL)
					{
						dp[i][x->val]=1;
						dp[x->val][i]=1;
						x=x->next;
					}
					dp[i][i]=0;	
				}
				for(int i=0;i<100;i++)
					for(int j=0;j<100;j++)
						for(int k=0;k<100;k++)
							if(dp[j][i]+dp[i][k]<dp[j][k])
								dp[j][k]=dp[j][i]+dp[i][k];
				int dmt=0;
				for(int i=0;i<100;i++)
					for(int j=0;j<100;j++)
						if(dp[i][j]!=1000 && dp[i][j]>dmt)
							dmt=dp[i][j];
				cout<<"Diameter: "<<dmt<<endl;
				break;
			}
			default:
			break;
		}
	}
	while(ch!=6);
	file.close();
	return 0;
}
void insert(int a,int b)
{
	Node* x=adjacencyList[a];
	if(x==NULL)
		adjacencyList[a]=new Node(b);
	else
	{
		while(x->next!=NULL)
			x=x->next;
		x->next=new Node(b);
	}
	return;
}
void insertResult(int a)
{
	Node* x=resultStore;
	if(x==NULL)
		resultStore=new Node(a);
	else
	{
		while(x->next!=NULL)
			x=x->next;
		x->next=new Node(a);
	}
	return;
}
void searchDFS(int v,int p)
{
	used[v]=true;
	insertResult(v);
	Node* x=adjacencyList[v];
	while(x!=NULL)
	{
		if(!used[x->val])
			searchDFS(x->val,v);
		else if(x->val!=p)
			isCycle=true;
		x=x->next;
	}
	return;
}

