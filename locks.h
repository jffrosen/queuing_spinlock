#ifndef __LOCKS_H__
#define __LOCKS_H__

/* Code for a spinlock where each thread (CPU) spins on a local
   variable, preventing cache coherence interference effects for
   highly contended locks.  Adapted from a CLH queue-based spinlock
   from 
   https://www.cs.rochester.edu/research/synchronization/pseudocode/timeout.html */

typedef struct qnode {
  volatile int must_wait;
  volatile struct qnode *volatile prev;
} qnode;

typedef volatile qnode qnode_t;
typedef qnode_t *lock_queue_t;

void acquire(lock_queue_t *L, qnode_t *I);
void release(lock_queue_t lock);

#endif
