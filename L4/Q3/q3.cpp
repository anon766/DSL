# include <bits/stdc++.h>
using namespace std;
int main()
{
	map <int, int> hashmap;
	int size,n;
	cin>>size;
	int* prefixSum=new int[size];
	cin>>prefixSum[0];
	for(int i=1; i<size; i++)
	{
		cin>>prefixSum[i];
		prefixSum[i]+=prefixSum[i-1];
		hashmap[prefixSum[i]]=i;
	}
	cin>>n;
	for(int i=0; i<size; i++)
	{
		if(i<hashmap[prefixSum[i]])
			hashmap[prefixSum[i]]=i;
	}
	int max=0, start=0, end=0, flag=0;
	for(int i=0; i<size; i++)
	{
		int index=prefixSum[i]-n;
		if(hashmap.find(index)!=hashmap.end())
		{
			flag=1;
			int diff=i-hashmap[index];
			if(diff>0 and diff>max)
			{
				max=diff;
				start=hashmap[index]+1;
				end=i;
			}
		}
	}	
	if(flag)
	{
		cout<<"\nLength of longest subarray is "<<max;
		cout<<"\nIndex from "<<start<<" to "<<end<<"\n";
	}
	else
		cout<<"\nNot Found\n";
}
