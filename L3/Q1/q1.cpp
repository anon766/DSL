# include <bits/stdc++.h>
using namespace std;
class Node
{
	public:
		int num;
		Node* left;
		Node* right;
		Node(int n)
		{
			num=n;
			left=NULL;
			right=NULL;
		}
		//virtual void insert() =0;
};
class BST 
{
	public: 
		Node* root;
		BST()
		{
			root=NULL;
		}
		/*Node* newNode(int n)
		{
			Node* node=new Node;
			node->num=n;
			node->right=NULL;
			node->left=NULL;
			return node;
		}*/
		void insert(Node* temp, int n)
		{	
			if(root==NULL)
			{
				root=new Node(n);
				return;
			}
			if(n>temp->num)
			{
				if(temp->right==NULL)
					temp->right=new Node(n);
				else
					insert(temp->right, n);
			}
			else if(n<temp->num)
			{
				if(temp->left==NULL)
					temp->left=new Node(n);
				insert(temp->left, n);
			}
		}	
		void inorderTraversal(Node* temp)
		{
			if(temp==NULL)
				return;
			inorderTraversal(temp->left);
			//cout<<temp->num<<"\n";
			cout<<temp->num<<"\n";
			inorderTraversal(temp->right);
			//cout<<temp->right<<"\n";
		}
		void printArr(int a[], int len)
		{
			for(int i=0; i<len; i++)
			{
				for(int j=i; j<len-1; j++)
				{
					cout<<a[j]<<"->";
				}
				cout<<a[len-1]<<"\n";
			}
		}
		void displayPaths(Node* temp, int a[], int len)
		{
			if(temp==NULL)
				return;
			a[len]=temp->num;
			len++;
			if(!temp->right && !temp->left)
			{
				printArr(a,len);
				return;
			}
			displayPaths(temp->left,a,len);
			displayPaths(temp->right,a,len);
		}
		void print(Node* temp, int level)
		{
			if(temp==NULL)
				return;
			for(int i=0; i<level; i++)
				cout<<"\t";
			cout<<temp->num<<"["<<level<<"]\n";
			print(temp->left, level+1);
			print(temp->right, level+1);
		}
};/*
class RedBlack : public BST
{
	public: 
		int colour;//!<0 is for black and 1 for red
};
class AVL : public BST
{
	public: 
		int height;
};		
void insert()*/
int main()
{
	BST treeBST;
	//AVL* treeAVL=NULL;
	//RedBlack* treeRB=NULL;
	do
	{
		int choice,n,a[100]={0},len=0,level=0;
		cout<<"\n\t\t\tMENU\n";
		cout<<"\n1. Insert in BST and Red-Black tree";
		cout<<"\n2. Create AVL tree";
		cout<<"\n3. Inorder traversal of BST/AVL/Red-Black";
		cout<<"\n4. Display all paths in BST/AVL/Red-Black";
		cout<<"\n5. Print BST/AVL/Red-Black with level-wise indentation";
		cout<<"\n6. Exit";
		cout<<"\nEnter your choice: ";
		cin>>choice;
		switch(choice)
		{
			case 1:	cout<<"Enter value of node: ";
				cin>>n;
				treeBST.insert(treeBST.root, n);
				//rootRB.insert(root, n);
				break;
			case 2: //rootAVL.create();
				break;
			case 3: treeBST.inorderTraversal(treeBST.root);
				//rootAVL.inorderTraversal();
				//rootRB.inorderTraversal();
				break;
			case 4: treeBST.displayPaths(treeBST.root, a, len);
				//rootAVL.displayPaths();
				//rootRB.displayPaths();
				break;
			case 5: treeBST.print(treeBST.root, level);
				//rootAVL.print();
				//rootRB.print();
				break;
			case 6: return 0;
		}
	}while(1);
}
