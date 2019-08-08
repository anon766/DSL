# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
/** 
 * Encrypts the string using the encryption key given in the question
 * @param str Stores the string that needs to be encrypted
 * @param n 
 * @param a 
 * @param b
 * @param output File pointer to the file into which the encrypted text is written
 */
void encrypt(char str[], int n, int a, int b, FILE* output)	
{	
	str[strcspn(str,"\n")]='\0';
	int len=strlen(str);
	int lenFinal=len;
	int multiple=len/n+1;
	if(len%n)
		lenFinal=multiple*n;
	for(int i=len; i<lenFinal+1; i++)
		str[i]='\0';
	int* indexOP=(int *)malloc(n*sizeof(int));
	///Finds the corresponding index of the output string 
	for(int i=0; i<n; i++)
		indexOP[i]=(a*i+b)%n;
	char* strOP=(char *)malloc(lenFinal*sizeof(char));
	///Stores the input string character at the correct index of output string using indexOP
	for(int i=0; i<multiple; i++)
	{
		for(int j=0; j<n; j++)
		{
			strOP[j+i*n]=str[indexOP[j]+i*n];
			if(strOP[j+i*n]=='\0')
			{
				printf("\\0");
				strOP[j+i*n]=224;
			}
			else
				printf("%c", strOP[j+i*n]);
		}
	}
	printf("\n");
	fprintf(output,"%s\n", strOP);
	free(indexOP);
	free(strOP);
}
/**
 * @param argc Contains the number of arguments including the program's name
 * @param argv Array of strings containing the arguments- n,a,b and original input file
 */
int main(int argc, char* argv[])
{
	clock_t t;
	t=clock();
	char str[100];
	int n,a,b;
	if(argc!=5)
	{
		printf("Error, not enough arguments");
		return 7;
	}
	n=atoi(argv[1]);
	a=atoi(argv[2]);
	b=atoi(argv[3]);
	if(n<1)
	{
		printf("Error, n has to be atleast 1");
		return 7;
	}
	if(a==0)
	{
		printf("Error, encryption not possible");
		return 7;
	}
	FILE* input=fopen(argv[4],"r");
	FILE* output=fopen("outputfile.txt", "wb");	
	while(fgets(str, 100, input))
	{
		encrypt(str,n,a,b,output);
	}
	fclose(input);
	fclose(output);
	char command[100]="./inverseTranspose ";
	for(int i=1; i<4; i++)
	{
		strcat(command,argv[i]);
		strcat(command," ");
	}
	strcat(command,"outputfile.txt");
	system(command);
	t=clock()-t;
	double cpuTime=((double)t)/CLOCKS_PER_SEC;
	printf("CPU time: %f\n", cpuTime);
       	return 0;
}	
