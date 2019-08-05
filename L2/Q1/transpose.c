# include <stdio.h>
# include <stdlib.h>
# include <string.h>
int main(int argc, char* argv[])
{
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
	FILE* input=fopen(argv[4],"r");
	FILE* output=fopen("outputfile.txt", "wb");	
	fgets(str, 100, input);
	str[strcspn(str,"\n")]='\0';
	//printf("String is: %s, length: %ld",str, strlen(str));
	int len=strlen(str);
	int lenFinal=len;
	int multiple=len/n+1;
	if(len%n)
		lenFinal=multiple*n;
	for(int i=len; i<lenFinal+1; i++)
		str[i]='\0';
	//printf("len :%d, lenFinal: %d, multiple: %d\n", len, lenFinal, multiple);
	int* indexOP=(int *)malloc(n*sizeof(int));
	for(int i=0; i<n; i++)
		indexOP[i]=(a*i+b)%n;
	char* strOP=(char *)malloc(lenFinal*sizeof(char));
	for(int i=0; i<multiple; i++)
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
			//fprintf(output,"%c", strOP[j+i*n]);
		}
	printf("\n");
	fprintf(output,"%s", strOP);
	free(indexOP);
	free(strOP);
	fclose(input);
	fclose(output);
	//fprintf(output,"%s", strOP);
	//printf("Encrypted string is: %s", strOP);
	char command[100]="./inverseTranspose ";
	for(int i=1; i<4; i++)
	{
		strcat(command,argv[i]);
		strcat(command," ");
	}
	strcat(command,"outputfile.txt");
	system(command);
       	return 0;
}	
	
