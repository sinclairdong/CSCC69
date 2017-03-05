#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

int start;

/* Page to evict is chosen using the fifo algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict() {
	//starting from start .... sure
	int frame = start;
	//++ index (the start of the FIFO queue)
	start++;
	//end case: if we are now at end of queue, go back to front of the queue
	// since allocate_frame() replaces the page
	//e.g. queue: 1,2,3.  remove 1 -> 4,2,3  remove 2 -> 4,5,3  remove 3 ->4,5,6
	if (start == memsize) { //if past end of queue (recall queue starts at 0)
		start = 0; //note that memsize is constant
	}

	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the fifo algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pgtbl_entry_t *p) {
	//N/A
	//return to make the compiler happy if it is not happy i am not happy =(
	return;
}

/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void fifo_init() {
	start = 0; 
}
