#include "time.h"
#include <errno.h>
#include <stdio.h>

struct timeval _t;

uint64 get_time(){
    if (gettimeofday(&_t, NULL)){
        printf("ERROR %d : could not get time\n", errno);
    }
    return (_t.tv_sec*1000000 + _t.tv_usec)/1000; //on a s et us, on veut ms
}
