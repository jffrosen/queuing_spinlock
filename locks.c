#include "locks.h"
#include "stdio.h"

void acquire(lock_queue_t *L, qnode_t *I) {
  // set this node's status to waiting and get predecessor
  I->next = NULL;
  qnode_t *predecessor = __sync_val_compare_and_swap(L, *L, I);

  if (predecessor != NULL){ // must wait
    I->locked = 1;
    predecessor->next = I;
    while (I->locked); //spin
  }
}

void release(lock_queue_t *L, qnode_t *I) {
  if (I->next == NULL) { // no known successor
    if (__sync_bool_compare_and_swap(L, I, NULL)) // are we still head?
      return;

    while (I->next == NULL); // wait for new node to change next
  }

  I->next->locked = 0; // unlock the new node
}
