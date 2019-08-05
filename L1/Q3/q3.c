# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# define cols 1268
# define rows 953
int **r;//!<Stores the value of red in the pixel
int **b;//!<Stores the value of blue in the pixel
int **g;//!<Stores the value of green in the pixel
/**
 * Reads the file containing pixel values
 * @param f File pointer 
 * @param num 2D array that contains value of that shade
 */
void read(FILE* f, int *num[cols])
{
	int i=0,j=0;
	while(fscanf(f, "%d,", &num[i][j])==1)
	{
		j++;
		if(j==cols)	
		{
			i++;
			j=0;
		}
	}
}
/**
 * Writes into the file to store the final rgb shades after removing green
 * @param f File pointer to the output file
 * @param num 2D array that contains the final value of the shades after removal of green
 */
void write(FILE* f, int *num[cols])
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols-1; j++)
		{
			fprintf(f,"%d,",num[i][j]);
		}
		fprintf(f,"%d\n",num[i][cols-1]);
	}
}
/**
 * Displayes the rgb shade at (x,y) coordinate
 * @param x x-coordinate
 * @param y y-coordinate
 */
void pixelValue(int x, int y)
{
	if(x<rows && x>=0 && y<cols && y>=0)
	{
		printf("\nRed: %d\t", r[x][y]);
		printf("Green: %d\t", g[x][y]);
		printf("Blue: %d\n", b[x][y]);
	}
	else
	{
		printf("\nError, out of bounds\n");
	}	
}
/**
 * Removes all red shades
 */
void redRemove()
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(r[i][j]>g[i][j] && r[i][j]>b[i][j])
				r[i][j]=0;
		}
	}
}
/**
 * Removes all green shades
 */
void greenRemove()
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(g[i][j]>r[i][j] && g[i][j]>b[i][j])
				g[i][j]=0;
		}
	}
}
/**
 * Removes all blue shades
 */
void blueRemove()
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(b[i][j]>g[i][j] && b[i][j]>r[i][j])
				b[i][j]=0;
		}
	}
}
/**
 * Keeps only red shades and removes blue and green shades
 */
void redOnly()
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(b[i][j]>g[i][j] && b[i][j]>r[i][j])
				b[i][j]=0;
			else if(g[i][j]>r[i][j] && g[i][j]>b[i][j])
				g[i][j]=0;
		}
	}
}
/** 
 * Keeps only green shades and removes red and blue shades
 */
void greenOnly()
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(b[i][j]>g[i][j] && b[i][j]>r[i][j])
				b[i][j]=0;
			else if(r[i][j]>g[i][j] && r[i][j]>b[i][j])
				r[i][j]=0;
		}
	}
}
/**
 * Keeps only blue shades and removes red and green shades
 */
void blueOnly()
{
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<cols; j++)
		{
			if(r[i][j]>g[i][j] && r[i][j]>b[i][j])
				r[i][j]=0;
			else if(g[i][j]>r[i][j] && g[i][j]>b[i][j])
				g[i][j]=0;
		}
	}
}
int main()
{
	clock_t t;
	t=clock();
	r = (int **)malloc(rows * sizeof(int *)); 
   	for (int i=0; i<rows; i++) 
       		r[i] = (int *)malloc(cols * sizeof(int));
	g = (int **)malloc(rows * sizeof(int *)); 
    	for (int i=0; i<rows; i++) 
        	g[i] = (int *)malloc(cols * sizeof(int));
	b = (int **)malloc(rows * sizeof(int *)); 
    	for (int i=0; i<rows; i++) 
        	b[i] = (int *)malloc(cols * sizeof(int));
	FILE *red,*green,*blue,*redOutput,*greenOutput,*blueOutput;
	red=fopen("Q3_ip_Red.dat","r");
	blue=fopen("Q3_ip_Blue.dat","r");
	green=fopen("Q3_ip_Green.dat","r");
	redOutput=fopen("RedOP.dat","w");
	greenOutput=fopen("GreenOP.dat","w");
	blueOutput=fopen("BlueOP.dat","w");
	if(!red || !blue || !green)
		printf("error\n");
	else
	{
		int x=0,y=0;
		read(red,r);
		read(green,g);
		read(blue,b);
		printf("\nEnter x value: ");
		scanf("%d", &x);
		printf("\nEnter y value: ");
		scanf("%d", &y);
		pixelValue(x-1,y-1);
		greenRemove();
		write(redOutput,r);
		write(greenOutput,g);
		write(blueOutput,b);
	}	
	free(r);
	free(g);
	free(b);
	fclose(red);
	fclose(green);
	fclose(blue);
	fclose(redOutput);
	fclose(greenOutput);
	fclose(blueOutput);
	t=clock()-t;
	double cpuTime=((double)t)/CLOCKS_PER_SEC;
	printf("\nCPU time: %f\n", cpuTime);
	return 0;
}
