/*
 * barriers for x86 processors
 */

#ifndef _BARRIER_H_
#define _BARRIER_H_

#if USE_BARRIER

#if defined(__i386__) || defined(__x86_64__)

#define read_barrier() \
	asm volatile("lfence":::"memory")

#define write_barrier() \
	asm volatile("sfence":::"memory")

#define barrier() \
	asm volatile ("mfence":::"memory")

#elif defined(__arm__)

#define read_barrier() \
	asm volatile("dmb":::"memory")

#define write_barrier() \
	asm volatile("dmb ishst" :::"memory")

#define barrier() \
	asm volatile ("dmb ish" :::"memory")

#endif /* ARCH */

#else /* USE_BARRIER */

#define read_barrier() do {} while(0)
#define write_barrier() do {} while(0)
#define barrier() do {} while(0)

#endif /* USE_BARRIER */

#endif /* _BARRIER_H_ */
