/*
 * barriers for x86 processors
 */

#ifndef _BARRIER_H_
#define _BARRIER_H_

#if USE_BARRIER
#define read_barrier() \
	asm volatile("lfence":::"memory")

#define write_barrier() \
	asm volatile("sfence":::"memory")

#define barrier() \
	asm volatile ("mfence":::"memory")

#else /* USE_BARRIER */

#define read_barrier() do {} while(0)
#define write_barrier() do {} while(0)
#define barrier() do {} while(0)

#endif /* USE_BARRIER */

#endif /* _BARRIER_H_ */
