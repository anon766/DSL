# include <stdio.h>
# include <stdlib.h>
# include <string.h>
int main(int argc, char* argv[])
{
	if(argc!=5)
	{
		printf("Error, not enought arguments\n");
		return 7;
	}
	int n,a,b,i=0;
	char inputStr[100];
	n=atoi(argv[1]);
	a=atoi(argv[2]);
	b=atoi(argv[3]);
	FILE* input=fopen(argv[4],"r");
	FILE* output=fopen("decryptedOutputfile.txt","w");
	/*while(fscanf(input, "%c", &inputStr[i])==1)
	{	
		i++;
	}*/
	fgets(inputStr, 100, input);
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
	char str[2];
	str[0]=224;
	str[1]='\0';
	outputStr[strcspn(outputStr,str)]='\n';	
	outputStr[strcspn(outputStr,str)]='\0';
	printf("Decrypted string is: %s", outputStr);
	fprintf(output,"%s",outputStr);
	free(index);
	free(outputStr);
	fclose(input);
	fclose(output);
	char command[100]="./compareFiles inputfile.txt decryptedOutputfile.txt";
	system(command);
	return 0;
}
	
