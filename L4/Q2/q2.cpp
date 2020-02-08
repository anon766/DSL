# include <bits/stdc++.h>
using namespace std;
/**
 * Makes a 2D array of n x n dimension.
 * @param board The 2D array
 * @param n The dimension of the square matrix
 */
int** makeBoard(int *board[], int n)
{
	board=new int*[n];
	for(int i=0; i<n; i++)
		board[i]=new int[n];
	return board;
}
/**
 * Prints the board with 1 as queen and 0 as empty boxes.
 * @param board The 2D array
 * @param n The dimension of the board
 */
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
/**
 * Checks if the current position of the new inserted queen is under attack due to already previous queens present on the board.
 * @param board The 2D array
 * @param x The row index
 * @param y The column index
 * @param n The dimension of the board.
 */
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
/**
 * Tries to find the possible solutions to N queen problem where N queens are placed in a NxN board, and each is not under attack due to the others.
 * @param board The 2D array
 * @param queenNumber The number of queens that are currently left to be placed
 * @param size The dimension of the board
 * @param count The number of solutions to the problem
 */
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
	clock_t t;
	t=clock();
	int size, **board=NULL, count=0;
	cin>>size;
	board=makeBoard(board, size);
	findBoard(board, size, size, count);
	cout<<"Total number of combinations: "<<count<<"\n";
	t=clock()-t;
	double cpuTime=double(t)/CLOCKS_PER_SEC;
	cout<<"CPU time :"<<cpuTime<<"\n";
}
	
