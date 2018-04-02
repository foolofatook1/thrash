/* 	
	Jacob Fisher 
	Thrashing lab03
	4/1/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 
   /proc/swaps:
   Filename	Type		Size		Used	Priority
   /dev/sda4	partition	3999740		0		-1
   _____________________________________________________________
   free -m:
   total	used	free	shared	buff/cache	available
Mem:	7904	1381	4356    	58		2166		6124
Swap:	3905	   0	3905		
_____________________________________________________________

PAGESIZE: 4096 **in bytes**
_____________________________________________________________
Program call should be as follows:
thrash MEGABYTES SECONDS MODIFY

MEGABYTES:	amount of mem to allocate.
SECONDS:	time spent on mem access, **excluding initial allocation**.
MODIFY:		1 if mem is to be modified as it is accessed.

Should add memory in frame-sized units.
Object is to rapidly visit and modify all frames so that operating systems
must replace and write back to disck a current frame.

#MAIN ALGORITHM:
1) Get three args as noted above.
2) Determine how many pages must be accessed based on MB 
to access and page size
3) Allocate memory for an array of pointers of type char (bytes).
4) For each element of the array allocate a number of bytes 
equal to page size.

while (time(NULL) - start_time < SECONDS)
{
# Create a random page number.
# Access the random buffer (page), changing at least one byte
if MODIFY is > 0
}
free all memory

# Before exiting program should print out the number of frames accessed per
second. By the way, you may want to use long rather than int if the values
are large. 
 */

#define PAGESIZE 4096

int main(int argc, char *argv[])
{
	srand(time(NULL));

	long frame_per_sec;
	long frames;

	long MEGABYTES;
	long SECONDS;
	int MODIFY = 0;

	long pages_to_access; /* based on MB to access and page size */

	int i;

	/* Get three args */
	if(argc < 2)
	{
		printf("Takes three arguments: MEGABYTES SECONDS MODIFY\n");
		return 0;
	}
	else if(argc == 3)
	{
		MEGABYTES = atoi(argv[1]);
		SECONDS = atoi(argv[2]);
	}
	else if(argc == 4)
	{
		MEGABYTES = atoi(argv[1]);
		SECONDS = atoi(argv[2]);
		MODIFY = atoi(argv[3]);
		if(MODIFY < 0)
		{
			printf("MODIFY must be >= 0");
			return 0;
		}
	}

	pages_to_access = (MEGABYTES*1000000)/PAGESIZE;
	char *pages[pages_to_access];

	/* Each element of array is equal to PAGESIZE. */
	for(i = 0; i < pages_to_access; ++i)
	{
		pages[i] = (char *) malloc(PAGESIZE);
		*pages[i] = i + '0';
		printf("%d %c\n", i, *pages[i]);
	}

	printf("Pages to access: %li\n", pages_to_access);

	long start_time = time(NULL);
	while(time(NULL) - start_time < SECONDS)
	{
		long rpn = rand()%pages_to_access; /* random page number */
		//if(MODIFY > 0)
		//pages[rpn] = 
	}

	/* Free allocated memory. */
	for(i = 0; i < pages_to_access; ++i)
		free(pages[i]);


	return 1;
}
