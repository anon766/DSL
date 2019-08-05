/**
 * @file stdio.h 
 * @brief This header file is used for standard input/output operations.
 */
# include <stdio.h>
/**
 * @file stdlib.h
 * @brief This header file is used for dynamic memory allocation.
 */
# include <stdlib.h>
/**
 * @file string.h
 * @brief This header file is used for string related operations.
 */
# include <string.h>
# include <time.h>
/**
 * This structure defines the data of each student
*/
typedef struct student
{
	int roll; //!< Contains the roll number of each student, starts from 101
	char name[30];
	char dob[10];//!< Date of Birth of the student
	char address[100];
	unsigned long int phone;
}student;
/**
 * This strucure defines a double linked list node containing student type data
 */
typedef struct list
{
	struct list* right;
	struct list* left;
	student data;
}list;
list* head=NULL;
int size=0;//!<Current size of the list
int currentRoll=101;//!<Stores the value of the roll number to be alloted to the new student
int top=0;//!<Defines the size of the unused roll number queue
int queue[13]={0};//!<Queue to store deleted roll numbers to be used for new students being enlisted
/**
 * This function is to insert a new node into the list, either at the beginning, middle or the end.
 * @param s contains the data of the student to be added into the list
 */
void insert(student s)
{
	list* l=(list*)malloc(sizeof(list));
	if(!l)
	{
		printf("\nError");
		return;
	}
	l->data=s;
	if(queue[0]==0)//if the queue is empty, then use currentRoll to allot roll number
	{
		l->data.roll=currentRoll;
		currentRoll++;
	}
	else
	{
		l->data.roll=queue[0];
		for(int i=0; i<top; i++)// used to shift the queue to the left
			queue[i]=queue[i+1];
		top--;
	}
	if(size==0)//if the current node is the first node to be inserted
	{
		head=l;
		head->right=head;
		head->left=head;
	}
	else
	{
		list* current=head;
		list* prev=head->left;
		int flag=0;//To check whether current node is being added in the beginning of the list
		int check=1;//To check if the current node hasn't rolled back to head
		while(current!=head || check)
		{		
			check=0;
			if(l->data.roll<current->data.roll)
			{
				if(current==head)	
					flag=1;
				break;
			}
			current=current->right;
			prev=prev->right;
		}
		prev->right=l;
		current->left=l;
		l->right=current;
		l->left=prev;
		if(flag)//Updates head to the current node since its the beginning of the list
			head=l;
	}
	size++;
}
/**
 * This function is to delete any node whose roll number that matches the roll number being passed into the function.
 * @param num The roll number of the node to be deleted. 
*/
void del(int num)
{
	if(size==0)
	{
		printf("\nList is empty");
		return;	
	}
	else
	{
		list* current=head;
		if(current->data.roll==num && size==1)//Checks whether there is only element in the list
		{
			free(current);
			head=NULL;
			size--;
		}
		else
		{
			int flag=1;
			while(current!=head || flag)
			{
				flag=0;
				if(current->data.roll==num)
				{
					list* temp=current->left;
					list* temp1=current->right;
					temp->right=temp1;
					temp1->left=temp;
					if(current==head)
						head=temp1;
					free(current);
					size--;
					queue[top++]=num; //Updates the unused roll number queue
					printf("\nRecord %d deleted\n", num);
					return;	
				}
				current=current->right;
			}
			printf("\nRecord not found\n");
		}
	}
}
/** 
 * Print the data of the student
 * @param data The data of the student to be displayed
 */
void print(student data)
{
	printf("\nRoll: %d", data.roll);
	printf("\nName: %s", data.name);
	printf("\nD.O.B: %s", data.dob);
}
/**
 * Modifies either name, dob, address, phone number of the node that matches the roll number passed into the function.
 * @ param num The roll number of the student to be modified
 */
void modify(int num)
{
	int choice=0;
	printf("\nWhat do you want to modify?");
	printf("\n1.Name");
	printf("\n2.DOB(dd-mon-yy)");
	printf("\n3.Address");
	printf("\n4.Phone number");
	printf("\nEnter choice: ");
	scanf("%d", &choice);
	list* temp=head;
	char str[100];//To enter new name, dob or address
	int n;//To enter new phone number 
	do
	{
		if(temp->data.roll==num)
		{
			switch(choice)
			{
				case 1: printf("\nEnter new name: ");
				       	scanf("%*c%[^\n]", str);
					strcpy(temp->data.name, str);
				       	break;
				case 2: printf("\nEnter new DOB: ");
					scanf("%*c%[^\n]", str);
					strcpy(temp->data.dob,str);
					break;
				case 3: printf("\nEnter new address: ");
					scanf("%*c%[^\n]", str);
					strcpy(temp->data.address, str);
					break;
				case 4: printf("\nEnter new phone number: ");
					scanf("%d", &n);
					temp->data.phone=n;
			}
			return;
		}	
		temp=temp->right;
	}while(temp!=head);
	printf("\nRecord not found");
}
/**
 * Sorts the list based on alphabetical order of name
 */
void sort()
{
	for(int i=0; i<size-1; i++)
	{
		list* temp=head;
		for(int j=0; j<size-i-1; j++)
		{
			list* current=temp;
			temp=temp->right;
			if(strcmp(current->data.name, temp->data.name)>0)
			{
				student temp1=current->data;
				current->data=temp->data;
				temp->data=temp1;
			}
		}
	}
}
/**
 * Reads the data of all the students in the file and stores them in array of student data type which is later used to insert in the list.
 * @param f The file which contains the data
 * @param records The array of records that contains data of each student
 */
void read(FILE* f, student records[])
{
	char arr[1000];
	int i=0;
	fgets(arr,1000,f);
	while(fgets(arr,1000,f))
	{
		char* token=strtok(arr,";");
		token= strtok(NULL,";");
		strcpy(records[i].name,token);
		token= strtok(NULL,";");
		strcpy(records[i].dob,token);
		token= strtok(NULL,";");
		strcpy(records[i].address,token);
		token= strtok(NULL,";");
		int num=atoi(token);
		records[i].phone=num;
		i++;	
	}
}
/**
 * Prints the entire list of data nodes.
 */
void printList()
{
	list* temp=head;
	int i=0;
	if(size==0)
		printf("\nError");
	else
	{
		print(head->data);
		temp=temp->right;
		while(temp!=head)
		{
			print(temp->data);
			temp=temp->right;
		}
		printf("\n");
	}
}
int main()
{
	clock_t t;
	t=clock();
	student s[13];//Contains data of all 13 students
	FILE* file; 
	file=fopen("StudentData.csv","r");
	read(file,s);
	del(108);
	insert(s[0]);
	insert(s[1]);
	insert(s[2]);
	insert(s[3]);
	del(102);
	del(101);
	insert(s[4]);
	insert(s[5]);
	insert(s[6]);
	printList();
	sort();
	printList();
	modify(103);
	printList();
	fclose(file);
	t=clock()-t;
	double cpuTime=((double)t)/CLOCKS_PER_SEC;
	printf("\nCPU time: %f\n", cpuTime);
	return 0;
}
