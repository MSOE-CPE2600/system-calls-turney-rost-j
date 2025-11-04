/**
 * @file      : info.c
 * @brief     : Displays system information using common information-maintenance system calls.
 *              Prints current time, OS info, CPU count, and memory details.
 * 
 * Author     : Jesse Rost <rostj@msoe.edu>
 * Date       : 11/02/25
 * Course     : CPE 2600
 * Section    : 112
 * Assignment : Lab 9
 * Algorithm  :
 *  - Get and print current system time using clock_gettime()
 *  - Retrieve and print hostname
 *  - Retrieve and print OS info with uname()
 *  - Print number of CPUs with get_nprocs()
 *  - Print memory info with sysinfo()
 *  - Print page size with getpagesize()
 */

// automatically includes the POSIX functions
// _POSIX_C_SOURCE 199309L - enables clockgettime()
// _POSIX_C_SOURCE 200809L - Adds functions like get_nprocs(), getline(), etc.
#define _GNU_SOURCE        // <-- enables gethostname() and getpagesize()

#include <stdio.h>
#include <time.h>
#include <sys/sysinfo.h>   // sysinfo(), get_nprocs()
#include <sys/utsname.h>   // uname()
#include <unistd.h>        // gethostname(), getpagesize(), sysconf()

int main(void)
{
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    printf("1. Current time of day       : %ld.%09ld seconds"
            "(nanosecond precision)\n",
           (long)t.tv_sec, (long)t.tv_nsec);

    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    printf("2. System network name       : %s\n", hostname);

    struct utsname uname_data;
    if (uname(&uname_data) == 0) {
        printf("3. Operating System Name     : %s\n", uname_data.sysname);
        printf("   OS Release                : %s\n", uname_data.release);
        printf("   OS Version                : %s\n", uname_data.version);
        printf("   Hardware Type             : %s\n", uname_data.machine);
    } else {
        perror("uname");
    }

    // get_nprocs() - gets the available number of CPU cores available
    int cpus = get_nprocs();
    printf("4. Number of CPUs            : %d\n", cpus);

    struct sysinfo info;
    // returns 0 if successful
    if (sysinfo(&info) == 0) {
        printf("5. Total Physical Memory     : %lu bytes\n", info.totalram);
        printf("   Total Free Memory         : %lu bytes\n", info.freeram);
    } else {
        // rare occurance but may happen if access is denied
        perror("sysinfo");
    }

    // getpagessize() - gets the mem page size
    long page_size = getpagesize();
    printf("6. Memory Page Size          : %ld bytes\n", page_size);

    return 0;
}
