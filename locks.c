#include "locks.h"
#include "stdio.h"

void acquire(lock_queue_t *L, qnode_t *I) {
  // set this node's status to waiting and get predecessor
  I->must_wait = 1;
  qnode_t *predecessor = __sync_val_compare_and_swap(L, *L, I);
  I->prev = predecessor;

  if (predecessor == NULL)
    return;

  // spin on local boolean
  while (predecessor->must_wait) {};
}

void release(qnode_t *I) {
  qnode_t *predecessor = I->prev;
  I->must_wait = 0;
  I = predecessor; // If still head of queue, set to NULL
}
