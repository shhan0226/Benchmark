#include <sys/time.h>
int millisecond(){
        struct timeval tv;
        struct timezone tzp;
        int secs;
        int usecs;
        int msecs;
        gettimeofday(&tv,&tzp);
        secs=tv.tv_sec;
        usecs=tv.tv_usec;
        msecs=1000*secs+usecs/1000;
        return(msecs);
}
     
