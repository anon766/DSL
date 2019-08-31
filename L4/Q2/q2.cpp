# include <bits/stdc++.h>
using namespace std;
int** makeBoard(int *board[], int n)
{
	board=new int*[n];
	for(int i=0; i<n; i++)
		board[i]=new int[n];
	return board;
}
void printBoard(int *board[], int n)
{
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			cout<<board[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\n";
}
bool checkQueen(int *board[], int x, int y, int n)
{
	for(int i=0; i<n; i++)
	{
		if(board[x][i]==1 or board[i][y]==1)
			return false;
	}
	for(int i=0; i<n; i++)
	{
		for(int j=0; j<n; j++)
		{
			if(i+j==x+y or i-j==x-y)
				if(board[i][j]==1)
					return false;
		}
	}
	return true;
}
void findBoard(int *board[], int queenNumber, int size, int& count)
{
	if(queenNumber==0)
	{
		printBoard(board, size);
		count++;
		return;
	}
	int start=size-queenNumber, flag=0, y=0;
	for(int i=0; i<size; i++)
	{
			if(checkQueen(board, start, i, size))
			{
				flag=1;
				board[start][i]=1;
				y=i;
				findBoard(board, queenNumber-1, size, count);
					board[start][i]=0;
			}
	}
}				
int main()
{
	int size, **board=NULL, count=0;
	cin>>size;
	board=makeBoard(board, size);
	findBoard(board, size, size, count);
	cout<<"Total number of combinations: "<<count<<"\n";
}
	
