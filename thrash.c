/* 	
Author: Jacob Fisher 
Lab: 	Thrashing lab03
Date: 	4/1/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main(int argc, char *argv[])
{
	long long MEGABYTES;		/* Amount of MB to allocate. */
	long long SECONDS;			/* Amount of time for allocation. */
	int MODIFY = 0;				/* Should we actually cause swapping? */
	long long PAGESIZE = 4096;	/* Preset pagesize for machine. */
	long long proc_per_sec; 	/* Final measure of frames accessed per second. */
	long long pages_to_access; 	/* Based on MB to access and page size */
	long long processes = 0;	/* Counts processes for proc_per_sec. */
	srand(time(NULL));			/* Necessary for producting sudo random nums. */
	char **pages;				/* Array of pages. */
	long long i;				/* Special i for loops. */

	/* Get three args */
	if(argc < 2)
	{
		printf("Takes three arguments: MEGABYTES SECONDS MODIFY\n");
		return -1;
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
			return -1;
		}
	}

	pages_to_access = (MEGABYTES*1048576)/PAGESIZE;
	pages = malloc(sizeof(char *)*pages_to_access);

	/* Each element of array is equal to PAGESIZE. */
	for(i = 0; i < pages_to_access; ++i)
	{
		pages[i] = malloc(PAGESIZE);
		/* Check to see if all was malloc'ed. */
		if(pages[i] == NULL)
		{
			printf("malloc was unsuccessful.\n");
			return -1;
		}
	}

	long long start_time = time(NULL); /* Time just before we start thrashing. */

	/* Run for given set time SECONDS and thrash if MODIFY > 0
	   by writing to (dirtying) each random index with a 
	   different character. 
	 */
	while(time(NULL) - start_time < SECONDS)
	{
		long long rpn = rand()%pages_to_access; /* random page number */
		if(MODIFY > 0)
		{
			++processes;
			char r = (char)rand();
			*pages[rpn] = r;
		}
	}

	proc_per_sec = processes/SECONDS;
	printf("Frames accessed per second: %lli\n", proc_per_sec);


	/* Free allocated memory. */
	for(i = 0; i < pages_to_access; ++i)
		free(pages[i]);
	free(pages);


	return 0;
}
