#include "cur_time.h"
#include <sys/time.h>


double cur_time(void)  
{
        struct timeval tv;
        /* struct timezone tz; */
        gettimeofday(&tv, 0 /* &tz */);
        return tv.tv_sec + tv.tv_usec*1.0e-6;
}
