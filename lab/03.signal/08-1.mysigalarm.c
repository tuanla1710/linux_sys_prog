#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <math.h>

/* number of times the handle will run: */
volatile int breakflag = 5;

void handle(int sig) {
    // printf("Hello\n");
    --breakflag;
    alarm(1);
}

void print_current_time_with_ms (void)
{
    long            ms; // Milliseconds
    time_t          s;  // Seconds
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    s  = spec.tv_sec;
    ms = round(spec.tv_nsec / 1.0e6); // Convert nanoseconds to milliseconds
    if (ms > 999) {
        s++;
        ms = 0;
    }

    printf("Current time: %"PRIdMAX".%03ld seconds since the Epoch\n",(intmax_t)s, ms);
}

int main() {
	time_t startTime;
	time_t rawtime;
	struct tm * timeinfo;
	
    signal(SIGALRM, handle);
    alarm(1);
	char input[10];
	startTime = time(NULL);
	// time ( &rawtime );
	// timeinfo = localtime ( &rawtime );
	// printf ( "Current local time and date: %s", asctime (timeinfo) );
	print_current_time_with_ms();
    while(time(NULL) < startTime + 4){ 
		continue;
	}
	print_current_time_with_ms();
	// timeinfo = localtime ( &rawtime );
	// printf ( "Current local time and date: %s", asctime (timeinfo) );
    printf("done\n");
    return 0;
}