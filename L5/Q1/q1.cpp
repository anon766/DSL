# include <bits/stdc++.h>
using namespace std;
void input(int a[], int n)
{
	int coeff=0, pow=0;
	while(n--)
	{
		cin>>coeff>>pow;
		a[pow]=coeff;
	}
}
void print(int a[])
{
	for(int i=99; i>=0; i--)
	{
		if(a[i]!=0)
			cout<<a[i]<<" "<<i<<"\n";
	}
}
void add(int a[], int b[], int n1, int n2)
{
	int c[100]={0};
	for(int i=0; i<100; i++)
		c[i]=a[i]+b[i];
	print(c);
}
void multiply(int a[], int b[], int n1, int n2)
{	
	int c[100]={0};
	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++)
			c[i+j]+=a[i]*b[j];
	print(c);
}
int main()
{
	int p1[100]={0}, p2[100]={0};
	int n1=0, n2=0;
	cout<<"No. of terms in expression: ";
	cin>>n1;
	input(p1, n1);
	cout<<"No. of terms in expression: ";
	cin>>n2;
	input(p2, n2);
	do
	{
		int choice;
		cout<<"\nEnter 1 to add or 2 for multiply: ";
		cin>>choice;
		if(choice==1)
			add(p1, p2, n1 ,n2);
		else if(choice==2)
			multiply(p1, p2, n1, n2);
		else
			cout<<"Error, try again\n";
	}while(1);
}
