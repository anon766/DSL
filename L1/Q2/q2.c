/**
 *	@file stdio.h
 *	@brief this header file contains standard input/output operations.
*/
# include <stdio.h>
/**
 * 	@file stdlib.h
 * 	@brief this header file is used for dynamic memory allocation.
*/
# include <stdlib.h>
# include <time.h>
//!number of elements in the queue currently
int currentSize=0;
//!maximum capacity of the queue
int maxSize=0;
/**
 *	This function is to print the entire queue.
 *	@param q pointer to the queue
*/
void print(int* q)
{
    	printf("List: ");
	for(int i=0; i<currentSize; i++)
       		printf("%d ", q[i]);
	printf("\nCurrent size of the dequeue is %ld bytes and capacity of dequeue is %ld bytes\n",currentSize*sizeof(int),maxSize*sizeof(int));
}
/**
 *	This function is to insert the element at the right of the queue.
 *	@param q pointer to the queue
*/
void insertR(int* q)
{
	if(currentSize==0)
	{
		q=realloc(q,1*sizeof(int)); 
		maxSize=1;
	}
	else if(currentSize==maxSize) //To check if the queue size is to be doubled
	{
		maxSize*=2;
		q=realloc(q,maxSize*sizeof(int));
	}
	printf("Enter element to be inserted at the right: ");
	scanf("%d", &q[currentSize]);
	currentSize++;
	print(q);
}
/**
 *      This function is to insert the element at the left of the queue.
 *      @param q pointer to the queue
*/

void insertL(int* q)
{
	if(currentSize==0)
	{
		q=realloc(q,1*sizeof(int));
		maxSize=1;	
	}
	else if(currentSize==maxSize)
	{
		maxSize*=2;
		q=realloc(q,maxSize*sizeof(int));//reallocates the memory alloted to queue
	}
	for(int i=currentSize; i>0; i--)//shifts the queue to the right to insert the new element in the front
		q[i]=q[i-1];
	printf("Enter element to be inserted at the left: ");
	scanf("%d", &q[0]);
	currentSize++;
	print(q);
}
/**
 *      This function is to delete the element at the right of the queue.
 *      @param q pointer to the queue
*/

void deleteR(int* q)
{
	if(currentSize==0)
	{
		printf("Deque is empty\n");
		return;
	}
	else
	{
		printf("The element that is being deleted from the right: %d\n",q[currentSize-1]);
		currentSize--;
		if(currentSize<=maxSize/2)// To check if the queue is to be halved
		{
			maxSize/=2;
			q=realloc(q,maxSize*sizeof(int));
		}
	}
    	print(q);
}
/**
 *      This function is to delete the element at the left of the queue.
 *      @param q pointer to the queue
*/

void deleteL(int* q)
{
	if(currentSize==0)
	{
		printf("Dequeue is empty\n");
		return;
	}
	else
	{
		printf("The element that is being deleted from the left: %d\n",q[0]);
		currentSize--;
		if(currentSize<=maxSize/2)
		{
			maxSize/=2;
			q=realloc(q,maxSize*sizeof(int));
		}
	}
	for(int i=0; i<currentSize; i++)//shifts the queue to the left, replacing the first value
		q[i]=q[i+1];
    	print(q);
}
int main()
{
	clock_t t;
	t=clock();
	int* q=(int*)malloc(1*sizeof(int));//intialises the queue with a size ofone
	int choice=0;
	do
	{
		printf("\t\t\tMENU\n");
		printf("\n1.Insert right");
		printf("\n2.Insert left");
		printf("\n3.Delete right");
		printf("\n4.Delete left");
		printf("\nPress any other key to exit");
		printf("\nEnter choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: insertR(q);
				break;
			case 2: insertL(q);
				break;
			case 3: deleteR(q);
				break;
			case 4: deleteL(q);
				break;
		}
	}while(choice<5 && choice>0);
	t=clock()-t;	
	double cpuTime=((double)t)/CLOCKS_PER_SEC;
	printf("\nCPU time: %f\n", cpuTime);
	return 0;
}
