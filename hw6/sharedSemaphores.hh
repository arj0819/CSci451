#include <fcntl.h>
#include <sys/stat.h> 
#include <semaphore.h>

// bring in necessary includes and define
// semaphore names with include guards (best practice)

// NOTE: Semaphore names must begin with "/" and cannot
//       contain any more "/" afterwards according to:
//       http://man7.org/linux/man-pages/man7/sem_overview.7.html

#ifndef SEM_ORDER
#define SEM_ORDER "/semOrder"
#endif
#ifndef SEM_OUT_OF_SEQUENCE
#define SEM_OUT_OF_SEQUENCE "/semOutOfSequence"
#endif
#ifndef SEM_PROCESS_COUNTER
#define SEM_PROCESS_COUNTER "/semProcessCounter"
#endif