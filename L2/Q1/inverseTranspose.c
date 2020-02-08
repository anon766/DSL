# include <stdio.h>
# include <stdlib.h>
# include <string.h>
/** 
 * Decrypts the encrypted text to obtain the original text
 * @param inputStr Contains the input string that needs to be decrypted
 * @param n
 * @param a
 * @param b
 * @param output File pointer to the file in which the decrypted text is written
 */
void decrypt(char inputStr[],int n, int a, int b, FILE* output)
{	
	inputStr[strcspn(inputStr,"\n")]='\0';
	int len=strlen(inputStr);
	char* outputStr=(char*)malloc(len*sizeof(char));
	int multiple=len/n;
	int* index=(int*)malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		index[i]=(a*i+b)%n;
	for(int i=0; i<multiple; i++)
	{
		for(int j=0; j<n; j++)
		{
			outputStr[index[j]+i*n]=inputStr[j+i*n];
		}
	}
	printf("Decrypted string is: ");
	for(int i=0; i<len; i++)
	{
		if(outputStr[i]!=char(224))
			printf("%c", outputStr[i]);
	}
	printf("\n");
	/*char str[2];
	str[0]=224;
	str[1]='\0';
	outputStr[strcspn(outputStr,str)]='\0';
	printf("Decrypted string is: %s\n", outputStr);*/
	fprintf(output,"%s\n",outputStr);
	free(index);
	free(outputStr);
}
/**
 * @param argc Contains the number of arguments being passed, including the program's name
 * @param argv Array of strings containing the list of arguments- n,a,b and encrypted text file
 */
int main(int argc, char* argv[])
{
	if(argc!=5)
	{
		printf("Error, not enought arguments\n");
		return 7;
	}
	int n,a,b;
	char inputStr[100];
	n=atoi(argv[1]);
	a=atoi(argv[2]);
	b=atoi(argv[3]);
	FILE* input=fopen(argv[4],"r");
	FILE* output=fopen("decryptedOutputfile.txt","w");
	while(fgets(inputStr, 100, input))
	{
		decrypt(inputStr,n,a,b,output);
	}
	fclose(input);
	fclose(output);
	char command[100]="./compareFiles inputfile.txt decryptedOutputfile.txt";
	system(command);
	return 0;
}	
