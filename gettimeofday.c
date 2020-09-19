#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    int *ptr;
    ptr = NULL;
    *(ptr) = 8;

    //printf("Time in seconds: %ld and usec: %ld along with the flag value is %d", current_time.tv_sec,current_time.tv_usec,flag);

}