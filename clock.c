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

	
	// let's use an int since we don't have boolean in C
	// I Know... C sucks.  :(
	int exit = 1;
	while(exit){
	    current = coremap[i].pte;
	    if((current->grame & PG_REF) == 0){
	        // return the index
	        exit = 0;
	    }else{
	        // now set it to not used since it has been checked
	        current->grame &= ~PG_REF;
	        i++;
	    }
	    
	    // need to move to start of coremap if next iteration is >= memsize
		// because we may have starting somewhere in the middle of coremap
		// and because we want to loop "circularly" until we find an unused PTE
		if(i + 1 >= memsize) {
			i = 0;
		}
	}
	return i;
}

/* This function is called on each access to a page to update any information
 * needed by the clock algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pgtbl_entry_t *p) {
	p->frame |= PG_REF;
	return;
}

/* Initialize any data structures needed for this replacement
 * algorithm. 
 */
void clock_init() {
    //i know i don't have to cuz it will be 0 anyway but that is good styleing
	i = 0;
}
