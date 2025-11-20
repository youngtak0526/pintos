#ifndef THREADS_SYNCH_H
#define THREADS_SYNCH_H

#include <list.h>
#include <stdbool.h>

/* A counting semaphore. */
struct semaphore {
	//현재 값 스레드를 담을 수 있는 양
	unsigned value;             /* Current value. */
	//대기하는 스레드의 리스트 
	struct list waiters;        /* List of waiting threads. */
};

void sema_init (struct semaphore *, unsigned value);
//P
void sema_down (struct semaphore *);
bool sema_try_down (struct semaphore *);
//V
void sema_up (struct semaphore *);
void sema_self_test (void);
/* Lock. */
struct lock {
	//이건 그냥 디버깅용 변수인듯
	struct thread *holder;      /* Thread holding lock (for debugging). */
	//이진 세마포어 그냥 락임 아마도 그냥 세마포어의 값을 1로 초기화해서 쓰는 거일듯함.
	struct semaphore semaphore; /* Binary semaphore controlling access. */
};

void lock_init (struct lock *);
//그냥 락을 거는 거일듯
void lock_acquire (struct lock *);
//락을 걸려고 시도는 하는데 이미 다른 스레드가 사용중이면 false를 반환하는 듯?
bool lock_try_acquire (struct lock *);
void lock_release (struct lock *);
bool lock_held_by_current_thread (const struct lock *);

/* Condition variable. */
struct condition {
	struct list waiters;        /* List of waiting threads. */
};

void cond_init (struct condition *);
void cond_wait (struct condition *, struct lock *);
void cond_signal (struct condition *, struct lock *);
void cond_broadcast (struct condition *, struct lock *);

/* Optimization barrier.
 *
 * The compiler will not reorder operations across an
 * optimization barrier.  See "Optimization Barriers" in the
 * reference guide for more information.*/
#define barrier() asm volatile ("" : : : "memory")

#endif /* threads/synch.h */
