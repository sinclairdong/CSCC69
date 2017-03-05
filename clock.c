#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the clock algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

int clock_evict() {
	pgtbl_entry_t *current;
	
	//clock starts at frame 0
	//i know i don't have to cuz it will be 0 anyway but that is good styleing
	i = 0;
	
	// let's use an int since we don't have boolean in C
	// I Know... C sucks.  :(
	int exit = 1;
	while(exit){
	    current = coremap[i].pte;
	}
	return 0;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {

	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
}
