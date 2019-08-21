# include <bits/stdc++.h>
using namespace std;
enum colour {red, black};//!<Declares enum to denote colour of node in red black tree where 0 is red and 1 is black
/**
 * Defines the node for all the trees , ie, BST, AVL, red black tree
 */
class Node
{
	public:
		int num;//!<Value of the node
		Node* left;//!<Point to left child
		Node* right;//!<Point to right child
		Node* parent;//!<Point to parent (used in Red Black tree)
		int height;//!<Stores height of node from deepest leaf in its subtrees
		int colour;//!<1 for black and 0 for red
		Node(int n)
		{
			num=n;
			height=1;
			left=NULL;
			right=NULL;
			parent=NULL;
			colour=red;
		}
};
/**
 * Defines Binary Search Tree with a root
 */
class BST 
{
	public: 
		Node* root;//!<Root of the tree
		BST()
		{
			root=NULL;
		}
		/**
		 * returns the height of the node.
		 * @param temp the node's height to be returned
		 */
		int getHeight(Node* temp)
		{
			if(temp==NULL)
				return 0;
			else
				return temp->height;
		}
		/**
		 * Insert node into the tree and calculates height of each node along the way and updates too.
		 * @param temp the node being inserted into the tree
		 * @param n the value of the node being inserted
		 */
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
    		/**
		 * Stores the inorder traversal in an array.
		 * @param temp the current node whose left and right child are going to be checked
		 * @param a the array in which the inorder traversal is stored
		 * @param size the size of the array
		 */		
		void getInorderTraversal(Node* temp, int a[], int &size)
		{
			if(temp==NULL)
				return;
			getInorderTraversal(temp->left, a, size);
			a[size]=temp->num;
			size++;
			getInorderTraversal(temp->right, a, size);
		}
		/**
		 * Prints the inorder traversal array.
		 * @param a the array containing the inorder traversal
		 * @param size the size of the array
		 */
		void printInorderTraversal(int a[], int size)
		{
			getInorderTraversal(root, a, size);
			for(int i=0; i<size; i++)
				cout<<a[i]<<" ";
		}
		/**
		 * Prints all the paths from node A to leaf node B. 
		 * @param a the array containing all the nodes between A and B
		 * @param len the length of the array
		 */
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
		/**
		 * Calculates all the paths by performing depth first search using recursion.
		 * @param temp the current node in the tree thats being searched recursively
		 * @param a the array containing all the nodes between A and B
		 * @param len the length of the array
		 */
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
		/**
		 * prints the level wise indentation of the tree in the terminal.
		 * @param temp the current node being printed
		 * @param level the depth of a node to decide the amount of indentation
		 */
		void print(Node* temp, int level)
		{
			if(temp==NULL)
				return;
			for(int i=0; i<level; i++)
				cout<<"\t";
			int balance=abs(getHeight(temp->left)-getHeight(temp->right));
			if(temp->right==NULL && temp->left==NULL)
				cout<<temp->num<<"\n";
			else
				cout<<temp->num<<"["<<balance<<"]"<<"\n";
			print(temp->left, level+1);
			print(temp->right, level+1);
		}
};
/**
 * Defines a Red Black Tree with proper insertion employing recolouring and rotations too
 */
class RBT : public BST
{
	public: 
		RBT():BST()
		{
		}
		/** 
		 * Performs a left rotation when balance>1 and returns the new root of the subtree after the rotation. 
		 * @param temp the node whose balance>1 and needs to be rotated
		 */
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
			temp->height=1+max(getHeight(temp->left), getHeight(temp->right));
			tempLeft->height=1+max(getHeight(tempLeft->left), getHeight(tempLeft->right));
			return tempLeft;
		}
		/** 
	 	 * Performs a right rotation when balance<1 and returns the new root of the subtree after the rotation .
		 * @param temp the node whose balance<1 and needs to be rotated
		 */
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
			temp->height=1+max(getHeight(temp->left), getHeight(temp->right));
			tempRight->height=1+max(getHeight(tempRight->left), getHeight(tempRight->right));
			return tempRight;
		}
		/**
		 * First tries to balance using recolouring and then using rotations.
		 * @param temp the current node who is violating red black tree property
		 */
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
		/**
		 * Insert a node into a red black tree.
		 * @param temp the current node being inserted
		 * @oaram n the value of the node
		 */
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
			temp->height=1+max(getHeight(temp->left), getHeight(temp->right));
			recolour(temp);
		}
		/**
		 * Prints level wise indentation along with colour of tree and balance factor.
		 * @param temp the current node being printed
		 * @param level the depth of a node
		 */
		void print(Node* temp, int level)
		{
			if(temp==NULL)
				return;
			for(int i=0; i<level; i++)
				cout<<"\t";
			int balance=abs(getHeight(temp->left)-getHeight(temp->right));
			if(temp->right==NULL && temp->left==NULL)
				cout<<temp->num;
			else
				cout<<temp->num<<"["<<balance<<"]";
			if(!temp->colour)
				cout<<"[RED]\n";
			else
				cout<<"[BLACK]\n";
			print(temp->left, level+1);
			print(temp->right, level+1);
		}

};
class AVL : public BST
{
	public: 
		int getBalance(int h1, int h2)
		{
			return h1-h2;
		}
		/**
		 * Performs a left rotation when balance>1 and returns the new root of the subtree after the rotation .
		 * @param temp the node whose balance>1 and needs to be rotated
		 */
		Node* leftRotate(Node* temp)
		{
			Node* tempLeft=temp->left;
			temp->left=tempLeft->right;
			tempLeft->right=temp;
			temp->height=1+max(getHeight(temp->left), getHeight(temp->right));
			tempLeft->height=1+max(getHeight(tempLeft->left), getHeight(tempLeft->right));
			return tempLeft;
		}
		/** 
		 * Performs a right rotation when balance<1 and returns the new root of the subtree after the rotation .
		 * @param temp the node whose balance<1 and needs to be rotated
		 */
		Node* rightRotate(Node* temp)
		{
			Node* tempRight=temp->right;
			temp->right=tempRight->left;
			tempRight->left=temp;
			temp->height=1+max(getHeight(temp->left), getHeight(temp->right));
			tempRight->height=1+max(getHeight(tempRight->left), getHeight(tempRight->right));
			return tempRight;
		}
		/**
		 * Inserts into a tree and checks for violation in balance factors and performing the appropriate rotations.
		 * @param temp the current node being inserted into the AVL tree
		 * @param n the value of the node
		 */
		Node* insert(Node* temp, int n)
		{
			if(temp==NULL)
			{
				temp=new Node(n);
				return temp;
			}
			if(n>temp->num)
			{
				temp->right=insert(temp->right, n);
			}
			else if(n<temp->num)
			{
				temp->left=insert(temp->left,n);
			}
			temp->height=1+max(getHeight(temp->right), getHeight(temp->left));
			int balance=getHeight(temp->left)-getHeight(temp->right);
			if(balance>1 && n<temp->num)
				temp=leftRotate(temp);
			else if(balance>1 && n>temp->num)
			{
				temp->right=rightRotate(temp->right);
				temp=leftRotate(temp);
			}
			else if(balance<-1 && n>temp->num)
				temp=rightRotate(temp);
			else if(balance<-1 && n<temp->num)
			{
				temp->left=leftRotate(temp->left);
				temp=rightRotate(temp);
			}
			return temp;
		}
		/**
		 * Creates an AVL tree using the inorder traversal array and inserts one by one.
		 * @param a stores the inorder traversal of the tree
		 * @param size stores the size of the array
		 */
		void create(int a[], int size)
		{
			root=NULL;
			for(int i=0; i<size; i++)
				root=insert(root,a[i]);
		}
};		
int main()
{
	clock_t t;
	t=clock();
	BST treeBST;
	AVL treeAVL;
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
			case 2: treeBST.getInorderTraversal(treeBST.root, a, size);
				treeAVL.create(a, size);
				break;
			case 3: cout<<"\nBST:\n";
				treeBST.printInorderTraversal(a, size);
				cout<<"\nAVL:\n";
				treeAVL.printInorderTraversal(a, size);
				cout<<"\nRed Black tree: \n";
				treeRBT.printInorderTraversal(a, size);
				break;
			case 4: cout<<"\nBST:\n";
				treeBST.displayPaths(treeBST.root, a, len);
				cout<<"\nAVL: \n";
				treeAVL.displayPaths(treeAVL.root, a, len);
				cout<<"\nRed Black tree: \n";
				treeRBT.displayPaths(treeRBT.root, a, len);
				break;
			case 5: cout<<"\nBST: \n";
				treeBST.print(treeBST.root, level);
				cout<<"\nAVL: \n";
				treeAVL.print(treeAVL.root, level);
				cout<<"\nRed Black tree: \n";
				treeRBT.print(treeRBT.root, level);
				break;
			case 6: t=clock()-t;
				double cpuTime=(double)t/CLOCKS_PER_SEC;
				cout<<"CPU time: "<<cpuTime<<"\n";
				return 0;
		}
	}while(1);
}
