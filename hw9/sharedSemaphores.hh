#include <fcntl.h>
#include <sys/stat.h> 
#include <semaphore.h>

// bring in necessary includes and define
// semaphore names with include guards (best practice)

// NOTE: Semaphore names must begin with "/" and cannot
//       contain any more "/" afterwards according to:
//       http://man7.org/linux/man-pages/man7/sem_overview.7.html

#ifndef SEM_OUT1
#define SEM_OUT1 "/semOut1"
#endif
#ifndef SEM_OUT2
#define SEM_OUT2 "/semOut2"
#endif
#ifndef SEM_OUT3
#define SEM_OUT3 "/semOut3"
#endif
#ifndef SEM_ORDER
#define SEM_ORDER "/semOrder"
#endif