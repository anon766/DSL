#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <limits.h>
#include <vector>
#include <string>

using namespace std;


class Graph
{
public:
	int adjList[26][26];
	int vertices;

	Graph()
	{
		for (int i = 0; i < 26; ++i)
		{
			for (int j = 0; i < 26; ++i)
			{
				adjList[i][j] = 0;
			}
		}
	}

	int getVertices()
	{
		int max = -7;
		for (int i = 0; i < 26; ++i)
		{
			int count = 0;
			for (int j = 0; j < 26; ++j)
			{
				if (adjList[i][j] > 0)
				{
					count = j+1;
				}
			}

			if (count > max)
			{
				max = count;
			}
		}
		return max;
	}

	void readFile(string fileName)
	{
		ifstream file;
		file.open(fileName);
		if (file.is_open())
		{
			char v1,v2;
			int weight;
			while(file>>v1>>v2>>weight)
			{
				this->addEdge(v1,v2,weight);
			}
			file.close();
		}
	}

	void addEdge(char v1, char v2, int weight)
	{
		adjList[v1-65][v2-65] = weight;
		adjList[v2-65][v1-65] = weight;
		this->vertices = getVertices();
	}

	void print()
	{
		int V = getVertices();
		for (int i = 0; i < V; ++i)
		{
			for (int j = i; j < V; ++j)
			{
				if (adjList[i][j] > 0)
				{
					cout << (char)(i+65) << ' ' << (char)(j+65) << ' ' << adjList[i][j] << endl;
				}	
			}
		}
	}

};

class HeapNode
{
public:
	HeapNode* parent;
	HeapNode* child;
	HeapNode* left;
	HeapNode* right;
	int num;
	int degree;
	char vertex, mark, c;

	HeapNode(char vertex,int weight)
	{
		this->vertex = vertex;
		this->num = weight;
	}
};


class Heap
{
public:
	HeapNode* rootMin;
	int countNodes;

	Heap()
	{
		rootMin = nullptr;
		countNodes = 0;
	}

	void insert(char v1, int weight)
	{
		HeapNode* node = new HeapNode(v1,weight);
		node->degree = 0;
		node->c = 'N';
		node->parent = nullptr;
		node->child = nullptr;
		node->left = node;
		node->right = node;
		if (rootMin != nullptr)
		{
			rootMin->left->right = node;
			node->right = rootMin;
			node->left = rootMin->left;
			rootMin->left = node;
			if (node->num < rootMin->num)
			{
				rootMin = node;
			}
		}
		else
		{
			rootMin = node;
		}
		countNodes++;
	}

	void join()
	{
		int temp1;
		int temp2 = (int)(log(countNodes)/log(2));

		HeapNode** arr = new HeapNode*[temp2+1];
		for (int i = 0; i <= temp2; ++i)
		{
			arr[i] = nullptr; 
		}

		HeapNode* ptr1 = rootMin;
		HeapNode* ptr2;
		HeapNode* ptr3;
		HeapNode* ptr4 = ptr1;

		do
		{
			ptr4 = ptr4->right;
			temp1 = ptr1->degree;
			while(arr[temp1] != nullptr)
			{
				ptr2 = arr[temp1];

				if (ptr1->num > ptr2->num)
				{
					ptr3 = ptr1;
					ptr1 = ptr2;
					ptr2 = ptr3;
				}

				if (ptr2 == rootMin)
				{
					rootMin = ptr1;
				}

				fibConnection(ptr2, ptr1);

				if (ptr1->right == ptr1)
				{
					rootMin = ptr1;
				}
				arr[temp1] = nullptr;
				temp1++;
			}

			arr[temp1] = ptr1;
			ptr1 = ptr1->right;

		}while(ptr1 != rootMin);

		rootMin = nullptr;

		for (int j = 0; j <= temp2; ++j)
		{
			if (arr[j] != nullptr)
			{ 

	            arr[j]->left = arr[j]; 
	            arr[j]->right = arr[j]; 

	            if (rootMin != nullptr)
	            { 
	                (rootMin->left)->right = arr[j]; 
	                arr[j]->right = rootMin; 
	                arr[j]->left = rootMin->left; 
	                rootMin->left = arr[j]; 
	                if (arr[j]->num < rootMin->num) 
	                {
	                    rootMin = arr[j]; 
	                }
	            } 
	            else
	            { 
	                rootMin = arr[j]; 
	            } 
	            if (rootMin == nullptr) 
	            {
	                rootMin = arr[j]; 
	            }
	            else if(arr[j]->num < rootMin->num) 
	            {
	                rootMin = arr[j]; 
	            }
        	}
		}

	}
	HeapNode* find(HeapNode* rootMin, char v) 
	{ 
		HeapNode* toReturn;
	    HeapNode* match = nullptr; 
	    HeapNode* temp5 = rootMin; 
	    temp5->c = 'Y'; 
	    HeapNode* match_ptr = nullptr;

	    if (temp5->vertex == v)
	    { 
	        match_ptr = temp5; 
	        temp5->c = 'N'; 
	        match = match_ptr; 
	        toReturn = match; 
	    } 
	    if (match_ptr == nullptr)
	    { 
	        if (temp5->child != nullptr)
	       	{ 
	            toReturn = find(temp5->child, v);
	        } 
	        if ((temp5->right)->c != 'Y')
	        {
	            toReturn = find(temp5->right, v); 
	        }
	    } 
	    temp5->c = 'N'; 
	    match = match_ptr; 

	    return toReturn;
	}


	HeapNode* extractMin()
	{
		HeapNode* ret = rootMin;
		if (rootMin != nullptr)
		{
			HeapNode* temp = rootMin; 
	        HeapNode* pntr; 
	        pntr = temp; 
	        HeapNode* x = nullptr; 
	        if (temp->child != nullptr) { 
	  
	            x = temp->child; 
	            do
	            { 
	                pntr = x->right; 
	                (rootMin->left)->right = x; 
	                x->right = rootMin; 
	                x->left = rootMin->left; 
	                rootMin->left = x; 
	                if (x->num < rootMin->num)
	               	{ 
	                    rootMin = x; 
	                }
	                x->parent = nullptr; 
	                x = pntr; 
	            } while (pntr != temp->child); 
	        } 

	        (temp->left)->right = temp->right; 
	        (temp->right)->left = temp->left; 
	        rootMin = temp->right; 

	        if (temp == temp->right && temp->child == nullptr) 
	        {
	            rootMin = nullptr; 
	        }
	        else
	        { 
	            rootMin = temp->right; 
	            join(); 
	        } 
	        countNodes--; 
		}

		return ret;


	}

	void cut(HeapNode* match, HeapNode* temp) 
	{ 
	    if (match == match->right)
	    { 
	        temp->child = nullptr; 
	    }
	  
	    (match->left)->right = match->right; 
	    (match->right)->left = match->left; 

	    if (match == temp->child) 
	    {
	        temp->child = match->right; 
	    }
	  
	    temp->degree = temp->degree - 1; 
	    match->right = match; 
	    match->left = match; 
	    (rootMin->left)->right = match; 
	    match->right = rootMin; 
	    match->left = rootMin->left; 
	    rootMin->left = match; 
	    match->parent = nullptr; 
	    match->mark = 'B'; 
	}

	void cutCasc(HeapNode* temp) 
	{ 
	    HeapNode* ptr5 = temp->parent; 
	    if (ptr5 != nullptr)
	    { 
	        if (temp->mark == 'W')
	        { 
	            temp->mark = 'B'; 
	        } 
	        else
	        { 
	            cut(temp, ptr5); 
	            cutCasc(ptr5); 
	        } 
	    } 
	}
	void fibConnection(HeapNode* ptr2, HeapNode* ptr1)
	{
		(ptr2->left)->right = ptr2->right; 
	    (ptr2->right)->left = ptr2->left; 

	    if (ptr1->right == ptr1)
	    { 
	        rootMin = ptr1; 
	    }

	    ptr2->left = ptr2; 
	    ptr2->right = ptr2; 
	    ptr2->parent = ptr1;

	    if (ptr1->child == nullptr) 
	    {
	        ptr1->child = ptr2; 
	    }
	    ptr2->right = ptr1->child; 
	    ptr2->left = (ptr1->child)->left; 
	    ((ptr1->child)->left)->right = ptr2; 
	    (ptr1->child)->left = ptr2; 

	    if (ptr2->num < (ptr1->child)->num) 
	    {
	        ptr1->child = ptr2; 
	    }

	    ptr1->degree++;
	}


	void decreaseKey(HeapNode* match, int val) 
	{ 
	    match->num = val; 
	  
	    HeapNode* temp = match->parent; 
	    if (temp != nullptr && match->num < temp->num)
	    { 
	        cut(match, temp); 
	        cutCasc(temp); 
	    } 
	    if (match->num < rootMin->num)
	    {
	        rootMin = match; 
	    }
	}


};


void newwick(vector<string>** wick,Graph* mst, char* parent,char v)
{
	for (int i=0; i < mst->vertices; ++i)
	{
		if ((char)(parent[i]+65) == v)
		{
			newwick(wick,mst,parent,(char)(i+65));
			string s = "";
			if (!wick[i]->empty())
			{
				s += "(";
				for (auto it = wick[i]->begin(); it != wick[i]->end(); ++it)
				{
					s += *it;
					if (*it != wick[i]->back())
					{
						s+= ",";
					}
				}
				s+= ")";
			}
			s+= (char)(i+65);
			s+= ':';
			s+= to_string(mst->adjList[i][v%65]);

			wick[v%65]->push_back(s);
		}
	}
}



int main(void)
{
	Graph* graph = new Graph();
	graph->readFile("input.txt");

	Heap* fibonacciHeap = new Heap();

	bool* mstSet = new bool[graph->vertices];
	char* parent = new char[graph->vertices];
	for (int i = 0; i < graph->vertices; ++i)
	{
		mstSet[i] = false;
		parent[i] = -1;
	}

	fibonacciHeap->insert((char)65,0);

	for (int i = 1; i < graph->vertices; ++i)
	{
		fibonacciHeap->insert((char)(i+65),INT_MAX);
	}

	for (int i = 0; i < graph->vertices - 1; ++i)
	{
		HeapNode* min = fibonacciHeap->extractMin();
		mstSet[min->vertex - 65] = true;

		for (int i = 0; i < graph->vertices; ++i)
		{
			HeapNode* node = fibonacciHeap->find(fibonacciHeap->rootMin,i+65);
			if (node != nullptr && graph->adjList[min->vertex - 65][i] != 0 && mstSet[i] == false && graph->adjList[min->vertex - 65][i] < node->num )
			{
				parent[i] = min->vertex - 65;
				fibonacciHeap->decreaseKey(node,graph->adjList[min->vertex - 65][i]);
			}
		}
	}

	Graph* mst = new Graph();
	int totalWeight = 0;
	for (int i = 0; i < graph->vertices; ++i)
	{
		int curr_weight = graph->adjList[i][parent[i]];
		totalWeight += curr_weight;
		mst->addEdge((char)(parent[i]+65), (char)(i+65), curr_weight);
	}

	mst->print();
	cout << endl;
	cout << "Total weight: " << totalWeight << endl;

	vector<string>** wick = new vector<string>*[mst->vertices];
	for (int i = 0; i < mst->vertices; ++i)
	{
		wick[i] = new vector<string>();
	}

	newwick(wick,mst,parent,'A');
	string s = "";
	if (!wick[0]->empty())
	{
		s += "(";
		for (auto it = wick[0]->begin(); it != wick[0]->end(); ++it)
		{
			s += *it;
			if (*it != wick[0]->back())
			{
				s+= ",";
			}
		}
		s+= ")";
	}
	s+="A;";

	ofstream file;
	file.open("prim.nw");
	if (file.is_open())
	{
		file << s << endl;
		file.close();
	}
	system("python etePrim.py");
	return 0;
}
