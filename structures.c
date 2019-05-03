#include <stdio.h>
#include <string.h>


//TODO: need to move this to my learning git repository, rather than here

typedef struct rectangle
{
	int length;
	int width;
	int area;
};

void area (struct rectangle *rect)
{
	rect->area = rect->length * rect->width;
}

int main(int argc, char *argv[])
{
	struct rectangle rect1;
	
	rect1.length = 10;
	rect1.width = 20;
	
	area(&rect1);
	
	printf("The area of rectange is %d.\n", rect1.area);
	
	return 0;
}
	
