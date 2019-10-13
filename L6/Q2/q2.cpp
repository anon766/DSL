# include <bits/stdc++.h>
# include <cmath>
using namespace std;
ofstream file;
class Node
{
	public:
		int data;
		int degree;
		Node *parent;
		Node* child;
		Node* sibling;
		Node(int n)
		{
			data = n;
			degree = 0;
			parent = sibling = child = NULL;
		}

};
class Heap 
{
	public:
		Node* root;
		int noOfTrees;
		Heap(int n)
		{
			root = NULL;
			noOfTrees = n; 
		}
		Node* mergeTree(Node *p, Node* c, int choice)
		{
			if(choice)
			{
				c->parent = p;
				c->sibling = p->child;
				p->child = c;
				if(c == root)
					root = p;
			}
			else
			{
				p->sibling = c->sibling;
				c->parent = p;
				c->sibling = p->child;
				p->child = c;
			}
			p->degree++;
			return p;
		}
		void mergeHeap()
		{
			Node* curr = root;
			Node* next = root->sibling;
			while(curr->sibling != NULL)
			{
				if(curr->degree >= next->degree)
				{
					if(curr->data < next->data)
					{
						curr = mergeTree(curr, next, 0);
						next = curr->sibling;
					}
					else 
					{
						next = mergeTree(next, curr, 1);
						curr = next;
						next = curr->sibling;
					}
				}
				else
				{
					curr = next;
					next = next->sibling;
				}
			}
		}
		void insert(int n)
		{
			Node *temp = new Node(n);
			if(root == NULL)
			{
				root = temp;
				return;
			}
			temp->sibling = root;
			root = temp;
			mergeHeap();
		}
		void printTree(Node *r)
		{	
			while(r)
				{
					cout<<r->data<<" ";
					printTree(r->child);
					r = r->sibling;
				}
		}
		void printHeap()
		{
			Node* r = root;
			//for(int i = 0; i < noOfTrees; i++)
			while(r)
			{
				cout<<"Order "<<r->degree<<": "<<r->data<<" ";
				printTree(r->child);
				cout<<"\n";
				r = r->sibling;
			}
		}
		void gviz(Node* r)
		{
			Node* x=r->child;
			if(x==NULL)
				file<<r->data<<";"<<endl;
			else
			{
			while(x)
			{
				file<<r->data<<" -- "<<x->data<<";"<<endl;
				x=x->sibling;
			}
			Node* y=r->child;
			while(y)
			{
				gviz(y);
				y=y->sibling;
			}
			}
		}
		void graphviz()
		{
			Node* r=root;
			while(r)
			{
				gviz(r);
				r=r->sibling;
			}
		}
};
int findOrder(int n)
{
	int count = 0;
	while(n)
	{
		if(n & 1)
			count++;
		n >>= 1;
	}
	return count;
}
int main()
{
	file.open("output.dot");
	file<<"graph G {"<<endl;
	int n;
	cin>>n;
	int *list = new int [n];
	int size = findOrder(n);
	Heap binomialHeap(size);
	for(int i = 0; i<n; i++)
		cin>>list[i];
	for(int i = 0; i<n; i++)
		binomialHeap.insert(list[i]);
	binomialHeap.printHeap();
	binomialHeap.graphviz();
	file<<"}"<<endl;
	file.close();
	system("dot -Tpng output.dot -o output.png");
}




