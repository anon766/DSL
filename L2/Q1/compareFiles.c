# include <stdio.h>
# include <stdlib.h>
# include <string.h>
/**
 * @param argc Contains the number of arguments being passed, including the program's name
 * @param argv Array of strings containing the list of arguments- original file and decrypted output file
 */
int main(int argc, char* argv[])
{
	if(argc!=3)
	{
		printf("Error, not enough arguments\n");
		return 7;
	}
	FILE* original,* decrypted;
	original=fopen(argv[1], "r");
	decrypted=fopen(argv[2],"r");
	char input[100],output[100];
	int flag=0;
	while(fgets(input,100,original) && fgets(output,100,decrypted))
	{
		if(strcmp(input,output))
		{
			flag=1;
			break;
		}
	}
	if(!flag)
		printf("The two texts match, the decryption is right\n");
	else
		printf("The two texts don't match, the decryption is incorrect\n");
	fclose(original);
	fclose(decrypted);
	return 0;
}

