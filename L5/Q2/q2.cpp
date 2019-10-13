# include <bits/stdc++.h>
using namespace std;

class Graph
{
	public:
		char v1;
		char v2;
		int weight;
		/*static int E;
		static int V;
		static int getE()
		{
			return E;
		}
		static int getV()
		{
			return V;
		}*/
}*g;
int E=0, V=0;
char* vertices;
/*class Graph
{
	public:
		int V;
		int E;
		Edge * edge;
		Graph(int e)
		{	
			E=e;
			edge=new Edge[E];
			V=0;
		}
};*/
class Set
{
	public: 
		int parent;
		int size;
};

int Find(Set* list, int v)
{
	if(list[v].parent!=v)
			list[v].parent=Find(list, list[v].parent);
	return list[v].parent;
}
void Union(Set* list, int v1, int v2)
{
	int parent1=Find(list, v1);
	int parent2=Find(list, v2);
	if(list[parent1].size>list[parent2].size)
	{
		list[parent2].parent=parent1;
		list[parent1].size++;
	}
	else
	{
		list[parent1].parent=parent2;
		list[parent2].size++;
	}
}
void getNoOfEdges()
{
	ifstream input("input.txt", ios::in);
	int edge=0;
	if(!input)
	{
		cout<<"Error";
		exit(-7);
	}
	string buf;
	while(getline(input, buf))
	{
		E++;
	}
	cout<<endl;
	input.close();
}
bool findVertex(char v, char list[])
{
	for(int i=0; i<V; i++)
		if(list[i]==v)
			return true;
	return false;
}
void createGraph()
{
	g=new Graph[E];
	ifstream input("input.txt", ios::in);
	if(!input)
	{
		cout<<"Error";
		exit(-7);
	}
	vertices=new char[E];
	int i=0;
	while(input>>g[i].v1>>g[i].v2>>g[i].weight)
	{
		if(!findVertex(g[i].v1, vertices))
			vertices[V++]=g[i].v1;
		else if(!findVertex(g[i].v2, vertices))
			vertices[V++]=g[i].v2;
		i++;
	}
	input.close();
}	
int compareWeight(const Graph &a, const Graph &b)
{
	return a.weight<b.weight;
}
void printMST(Graph *mst)
{	
	int sum=0;
	ofstream file("output.dot", ios::out);
	file<<"graph G {\n";
	for(int i=0; i<V-1; i++)
	{
		sum+=mst[i].weight;
		cout<<mst[i].v1<<" "<<mst[i].v2<<" "<<mst[i].weight<<"\n";
		file<<mst[i].v1<<" -- "<<mst[i].v2<<" [label="<<mst[i].weight<<"];\n";
	}
	file<<"}";
	file.close();
	cout<<"Total weight: "<<sum<<"\n";
}
void KrushkalMST()
{
	sort(g, g+E, compareWeight);
	int count=0, edgeCount=0;
	Graph *mst=new Graph[E];
	Set *list;
	list=new Set[V];
	for(int i=0; i<V; i++)
	{
		list[i].parent=i;
		list[i].size=0;
	}
	while(edgeCount<(V-1) && count<E)
	{
		int v1=g[count].v1-'A';
		int v2=g[count].v2-'A';
		int parent1=Find(list, v1);
		int parent2=Find(list, v2);
		if(parent1!=parent2)
		{
			mst[edgeCount]=g[count];
			edgeCount++;
			Union(list, parent1, parent2);
		}
		count++;
	}
	printMST(mst);
}
int main()
{
	getNoOfEdges();
	createGraph();
	KrushkalMST();
}
