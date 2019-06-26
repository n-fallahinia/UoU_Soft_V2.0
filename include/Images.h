#ifndef IMAGES_H
#define IMAGES_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


class Images
{
public:
	int cols;
	int rows;
	int inc;
//	int num;
	
//	int max_num;
	
	
	Images();
	Images(int, int, int );
	Images(int, int, int, unsigned char *);
	Images(Images *);
	~Images();
	
	void readImage(unsigned char *);
	void writeImage(int, int, int, unsigned char *);
	void writeImage(unsigned char *);
	
	
private:
	unsigned char *data;
	
};

inline void ppm_write(char *filename, int width, int height, unsigned char* data)
{
	int num;
	int size = width * height * 3;

	FILE *fp = fopen(filename, "wb");

	if (!fp) 
	{
		printf("Cannot open file %s for writing\n",filename);
		exit(0);
	}

	fprintf(fp, "P6\n%d %d\n%d\n", width, height, 255);

	num = (int) fwrite((void *) data, 1,  size, fp);
	
	fclose(fp);
	

	printf("Writing image %s of size [%d,%d]\n",filename,height,width);


	if (num != size) 
	{
		return;
	}
} 

#endif
