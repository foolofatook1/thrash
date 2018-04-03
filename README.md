*Program call should be as follows:*
thrash MEGABYTES SECONDS MODIFY

**MEGABYTES:**	amount of mem to allocate.

**SECONDS:**	time spent on mem access, *excluding initial allocation*.

**MODIFY:**		1 if mem is to be modified as it is accessed.

Should add memory in frame-sized units.
Object is to rapidly visit and modify all frames so that operating systems
must replace and write back to disck a current frame.

**MAIN ALGORITHM:**
1) Get three args as noted above.
2) Determine how many pages must be accessed based on MB 
to access and page size
3) Allocate memory for an array of pointers of type char (bytes).
4) For each element of the array allocate a number of bytes 
equal to page size.

while (time(NULL) - start_time < SECONDS)

{

	Create a random page number.

	Access the random buffer (page), changing at least one byte

	if MODIFY is > 0

}

*free all memory*

Before exiting program should print out the number of frames accessed per
second. By the way, you may want to use long rather than int if the values
are large. 

