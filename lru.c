#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <limits.h>
#include "pagetable.h"


extern int memsize;

extern int debug;

extern struct frame *coremap;

/* Page to evict is chosen using the accurate LRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */

pgtbl_entry_t *lru_pte;
unsigned long max_time;
int lru_evict() {

    // keep track of last minimum
	pgtbl_entry_t *last_lru_pte = lru_pte; 
	// the current pte
	pgtbl_entry_t *current; 
	
	
	// for the for loop
	int i; 
	// the return value; index of coremap[]
	int frame;
	//to set it to the maximum value thus everyother value will be smaller than it ULONG_MAX is from limits.h
	unsigned long min = ULONG_MAX;
	for(i = 0; i < memsize; i++){
	    current = coremap[i].pte;
	    if(current->frame & PG_VALID){
	        //see if it is in the memory
	        if(current != last_lru_pte){
	            if(current->time_stamp < min){
	                //the new mininum
                    min = current->time_stamp;
                    lru_pte = current;
                }
	        }
	    }
	    if(current == last_lru_pte){
	        frame = i;
	    }
	}
	return frame;
}

/* This function is called on each access to a page to update any information
 * needed by the lru algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void lru_ref(pgtbl_entry_t *p) {
	if (lru_pte == NULL){
	    //initialize if it doesn't exist
		lru_pte = p;
	}
	p->time_stamp = max_time; //assign the timestamp to this pte
	max_time++; //increment timestamp

	if(max_time == ULONG_MAX) { 
	    // care for overflow
		perror("may overflow with max_timestamp in lru");
		exit(1);
	}
}


/* Initialize any data structures needed for this 
 * replacement algorithm 
 */
void lru_init() {
    lru_pte = NULL;
	max_time = 0;
}
