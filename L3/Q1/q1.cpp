# include <bits/stdc++.h>
using namespace std;
enum colour {red, black};
class Node
{
	public:
		int num;
		Node* left;
		Node* right;
		Node* parent;
		int height;
		int colour;//!<0 for black and 1 for red
		Node(int n)
		{
			num=n;
			height=1;
			left=NULL;
			right=NULL;
			parent=NULL;
			colour=red;
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
		int getHeight(Node* temp)
		{
			if(temp==NULL)
				return 0;
			else
				return temp->height;
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
				else
					insert(temp->left, n);
			}
			temp->height=1+max(getHeight(temp->right), getHeight(temp->left));
		}	
		void getInorderTraversal(Node* temp, int a[], int &size)
		{
			if(temp==NULL)
				return;
			getInorderTraversal(temp->left, a, size);
			//cout<<temp->num<<"\n";
			a[size]=temp->num;
			size++;
			getInorderTraversal(temp->right, a, size);
		}
		void printInorderTraversal(int a[], int size)
		{
			getInorderTraversal(root, a, size);
			for(int i=0; i<size; i++)
				cout<<a[i]<<"\n";
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
			cout<<temp->num<<"["<<level<<"]"<<"\n";
			print(temp->left, level+1);
			print(temp->right, level+1);
		}
};
class RBT : public BST
{
	public: 
		RBT():BST()
		{
		}
		Node* leftRotate(Node* temp)
		{
			Node* tempLeft=temp->left;
			temp->left=tempLeft->right;
			if(tempLeft->right)
			{
				tempLeft->right->parent=temp;
			}
			tempLeft->parent=temp->parent;
			if(temp->parent==NULL)
				root=tempLeft;
			else if(temp->parent->left==temp)
				temp->parent->left=tempLeft;
			else
				temp->parent->right=tempLeft;
			temp->parent=tempLeft;
			tempLeft->right=temp;
			return tempLeft;
		}
		Node* rightRotate(Node* temp)
		{
			Node* tempRight=temp->right;
			temp->right=tempRight->left;
			if(tempRight->left)
			{
				tempRight->left->parent=temp;
			}
			tempRight->parent=temp->parent;
			if(temp->parent==NULL)
				root=tempRight;
			else if(temp->parent->left==temp)
				temp->parent->left=tempRight;
			else
				temp->parent->right=tempRight;
			temp->parent=tempRight;
			tempRight->left=temp;
			return tempRight;
		}
		void recolour(Node* temp)
		{
			Node* parent=NULL;
			Node* grandparent=NULL;
			while(temp!=root && temp->parent->colour==red && temp->colour==red)
			{
				parent=temp->parent;
				grandparent=temp->parent->parent;
				if(grandparent->left==parent)//LL or LR
				{
					Node* uncle=grandparent->right;
					if(uncle && uncle->colour==red)
					{
						parent->colour=black;
						uncle->colour=black;
						grandparent->colour=red;
						temp=grandparent;
					}
					else 
					{
						if(temp->num>parent->num)
							parent=rightRotate(parent);
						swap(grandparent->colour, parent->colour);
						grandparent=leftRotate(grandparent);
						temp=parent;
					}
				}
				else//RR or RL 
				{
					Node* uncle=grandparent->left;
					if(uncle && uncle->colour==red)
					{
						parent->colour=black;
						uncle->colour=black;
						grandparent->colour=red;
						temp=grandparent;
					}
					else 
					{
						if(temp->num<parent->num)
							parent=leftRotate(parent);
						swap(grandparent->colour, parent->colour);
						grandparent=rightRotate(grandparent);
						temp=parent;
					}
				}
			}		
			root->colour=black;
		}
		void insert(Node* temp, int n)
		{
			if(root==NULL)
			{
				root=new Node(n);
				root->colour=black;
				return;
			}
			else if(n>temp->num)
			{
				if(temp->right==NULL)
				{
					temp->right=new Node(n);
					temp->right->parent=temp;
					temp=temp->right;
				}
				else
					insert(temp->right, n);
			}
			else if(n<temp->num)
			{
				if(temp->left==NULL)
				{
					temp->left=new Node(n);
					temp->left->parent=temp;
					temp=temp->left;
				}	
				else
					insert(temp->left, n);
			}
			recolour(temp);
		}
		void print(Node* temp, int level)
		{
			if(temp==NULL)
				return;
			for(int i=0; i<level; i++)
				cout<<"\t";
			cout<<temp->num<<"["<<level<<"]";
			if(temp->colour)
				cout<<"RED\n";
			else
				cout<<"BLACK\n";
			print(temp->left, level+1);
			print(temp->right, level+1);
		}

};
/*class AVL : public BST
{
	public: 
		void getBalance(int h1, int h2)
		{
			return h1-h2;
		}
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
				else
					 insert(temp->left,n);
			}
			temp->height=1+max(getHeight(temp->right), getHeight(temp->left));
			int balance=getHeight(temp->left)-getHeight(temp->right);
			if(balance>1 && n>temp->num)
			{

		void create(int a[], int size)
		{
			for(int i=0; i<size; i++)
				insert(root,a[i]);
		}
};*/		
int main()
{
	BST treeBST;
	//AVL treeAVL;
	RBT treeRBT;
	do
	{
		int choice,n,a[100]={0},size=0,len=0,level=0;
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
				treeRBT.insert(treeRBT.root, n);
				break;
			case 2: //treeBST.getInorderTraversal(a, size);
				//treeAVL.create(a, size);
				break;
			case 3: treeBST.printInorderTraversal(a, size);
				//rootAVL.inorderTraversal();
				treeRBT.printInorderTraversal(a, size);
				break;
			case 4: treeBST.displayPaths(treeBST.root, a, len);
				//rootAVL.displayPaths();
				treeRBT.displayPaths(treeRBT.root, a, len);
				break;
			case 5: treeBST.print(treeBST.root, level);
				//rootAVL.print();
				treeRBT.print(treeRBT.root, level);
				break;
			case 6: return 0;
		}
	}while(1);
}
