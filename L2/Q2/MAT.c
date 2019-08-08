# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>
/**
 * Defines the data of each node in the quadtree
 */
typedef struct node
{
	int label;//!<Stores the corresponding block number alloted to the node in maxArr
	int bit;//!<Identifies whether its part of the image or outside the image
	int level;//!<Stores the depth of the node in the quadtree
}node;
/**
 * Defines the quadtree containing the nodes
 */
typedef struct quadtree
{
	struct quadtree* nw;//!<North-West node
	struct quadtree * ne;//!<North-East node
	struct quadtree* sw;//!<South-west node
	struct quadtree* se;//!<South-east node
	node data;//!<Contains label, bit, and level information of that node
}quadtree;
int **imageBin;//!<Contains the original input of image array, where 0 means outside the image and 1 is part of the image
int **maxArr;//!<Stores the corresponding block number to a part outside or inside the image
int counter=1; //!<Keeps a count of how many blocks have been allotted currently
quadtree* root;//!<Declares the quadtree
/**
 * Fetches the dimension of the matrix of image array in order to dynamically allocate for storage.
 * @param f File pointer
 */
int dimension(FILE* f)
{
	int count=0,num;
	while(fscanf(f, "%d ", &num)==1)
	{
		count++;
	}
	return sqrt(count);
}
/**
 * Reads the image array in binary format and stores in the dynamically allocated 2D array.
 * @param f File pointer
 * @param size Stores the least order of 2 dimension that is greater than the image array dimension in order to split evenly at every split
 * @param dimension Stores the dimension of the image array
 */
void read(FILE* f, int size, int dimension)
{
	int i=size-dimension,j=size-dimension;
	while(fscanf(f, "%d", &imageBin[i][j])==1)
	{
		j++;
		if(j==size)
		{
			i++;
			j=size-dimension;
		}
	}
}
/**
 * Creates the maxArr that stores corresponding block number of the image array.
 * @param xStart Stores the starting row index of the quadrant
 * @param xEnd Stores the ending row index of the quadrant
 * @param yStart Stores the starting column index of the quadrant
 * @param yEnd Stores the ending column index of the quadrant
 */
void createMaximalArr(int xStart, int xEnd, int yStart, int yEnd)
{
	int check=imageBin[xStart][yStart], flag=1;
	int newSize=(xEnd-xStart)/2;
	for(int i=xStart; i<xEnd; i++)
	{
		for(int j=yStart; j<yEnd; j++)
		{
			if(imageBin[i][j]!=check)
			{
				flag=0;
				createMaximalArr(xStart, xEnd-newSize, yStart, yEnd-newSize);
				createMaximalArr(xStart, xEnd-newSize, yEnd-newSize, yEnd);
				createMaximalArr(xEnd-newSize, xEnd, yStart, yEnd-newSize);
				createMaximalArr(xEnd-newSize, xEnd, yEnd-newSize, yEnd);
				break;
			}
		}
		if(flag==0)
			break;
	}
	if(flag)
	{
		for(int i=xStart; i<xEnd; i++)
			for(int j=yStart; j<yEnd; j++)
				maxArr[i][j]=counter;
		counter++;
	}
}
/**
 * Inserts a new node to the quadtree and returns the new node
 */
quadtree* insert()
{
	quadtree* temp=(quadtree*)malloc(1*sizeof(quadtree));
	temp->nw=NULL;
	temp->ne=NULL;
	temp->sw=NULL;
	temp->se=NULL;
	temp->data.label=0;
	temp->data.bit=-1;
	temp->data.level=0;
	return temp;
}
/**
 * Finds the current depth of the inserted node from root, where level of root is 0.
 * @param temp Stores the current position of the node from where subsequent search occurs
 * @param q Stores the node whose level is to be found
 * @param level Stores the level of the node, and receives an intial value of 0
 */
int checkLevel(quadtree* temp, quadtree* q, int level)
{
	if(temp!=NULL && temp!=q)
	{
		int tempLevel=checkLevel(temp->nw,q,level+1);
		if(tempLevel!=-1)
			return tempLevel;
		tempLevel=checkLevel(temp->ne,q,level+1);
		if(tempLevel!=-1)
			return tempLevel;
		tempLevel=checkLevel(temp->sw,q,level+1);
		if(tempLevel!=-1)
			return tempLevel;
		tempLevel=checkLevel(temp->se,q,level+1);
		if(tempLevel!=-1)
			return tempLevel;
	}
	if(temp==q)	
		return level;
	else 
		return -1;
}
/**
 * Creates the quadtree of the image array.
 * @param xStart Stores the starting row index of the quadrant
 * @param xEnd Stores the ending row index of the quadrant
 * @param yStart Stores the starting column index of the quadrant
 * @param yEnd Stores the ending column index of the quadrant
 * @param temp Stores the current node from where branching may occur or block number be allotted
 */
void createQuadtree(int xStart, int xEnd, int yStart, int yEnd, quadtree* temp)
{
	int check=imageBin[xStart][yStart], flag=1;
	int newSize=(xEnd-xStart)/2;
	for(int i=xStart; i<xEnd; i++)
	{
		for(int j=yStart; j<yEnd; j++)
		{
			if(imageBin[i][j]!=check)
			{
				flag=0;
				temp->nw=insert();
				temp->ne=insert();
				temp->sw=insert();
				temp->se=insert();
				createQuadtree(xStart, xEnd-newSize, yStart, yEnd-newSize,temp->nw);
				createQuadtree(xStart, xEnd-newSize, yEnd-newSize, yEnd,temp->ne);
				createQuadtree(xEnd-newSize, xEnd, yStart, yEnd-newSize,temp->sw);
				createQuadtree(xEnd-newSize, xEnd, yEnd-newSize, yEnd,temp->se);
				break;
			}
		}
		if(flag==0)
			break;
	}
	if(flag)
	{
		for(int i=xStart; i<xEnd; i++)
			for(int j=yStart; j<yEnd; j++)
				maxArr[i][j]=counter;
		temp->data.label=counter;
		temp->data.bit=check;
		temp->data.level=checkLevel(root, temp, 0);
		counter++;
	}
}
/** 
 * Prints the tree using post order traversal.
 * @param temp Stores the current node from where further traversal will take place
 */
void printTree(quadtree* temp)
{
	if(temp==NULL)
		return;
	else
	{
		printTree(temp->nw);
		printTree(temp->ne);
		printTree(temp->sw);
		printTree(temp->se);
		printf("(%d, %d, %d)\n",temp->data.label, temp->data.bit, temp->data.level);
	}
}
/**
 * Prints the 2D array.
 * @param arr Stores the array to be printed
 * @param size Stores the dimension of the square matrix
 */
void print(int *arr[], int size)
{
	for(int i=0; i<size; i++)
	{
		for(int j=0; j<size-1; j++)
			printf("%3d", arr[i][j]);
		printf("%3d\n", arr[i][size-1]);
	}
	printf("\n");
}
int main()
{
	clock_t t;
	t=clock();
	root=insert();
	FILE* input=fopen("input.txt","r");
	int dim=dimension(input);
	fseek(input,0,SEEK_SET);
	int size=1;
	for(; size<dim; size*=2);
	imageBin=(int**)malloc(size*sizeof(int*));
	for(int i=0; i<size; i++)
		imageBin[i]=(int*)malloc(size*sizeof(int));
	maxArr=(int**)malloc(size*sizeof(int*));
	for(int i=0; i<size; i++)
		maxArr[i]=(int*)malloc(size*sizeof(int));
	read(input,size, dim);
	createMaximalArr(0, size, 0, size);
	counter=1;
	createQuadtree(0, size, 0, size, root);
	printf("Maximal Array: \n");
	print(maxArr,size);
	printf("Quadtree nodes: \n");
	printTree(root);
	free(imageBin);
	free(maxArr);	
	fclose(input);
	t=clock()-t;
	double cpuTime=((double)t)/CLOCKS_PER_SEC;
	printf("CPU time: %f\n", cpuTime);
	return 0;
}
	
