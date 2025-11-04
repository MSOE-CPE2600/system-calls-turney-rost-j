/**
 * @file      : pmod.c
 * @brief     : Modifies process priority and pauses using nanosleep.
 * 
 * Author     : Jesse Rost <rostj@msoe.edu>
 * Date       : 11/02/25
 * Course     : CPE 2600
 * Section    : 112
 * Assignment : Lab 9
 * Algorithm  :
 *  - Retrieve current process priority using getpriority()
 *  - Decrease process priority by 10 using nice() (increase niceness)
 *  - Confirm and display new priority
 *  - Sleep for 1.837272638 seconds using nanosleep()
 *  - Print completion message before exiting
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/resource.h>

int main(void) {
    int old_priority, new_priority;

    // Get current priority
    errno = 0;
    old_priority = getpriority(PRIO_PROCESS, 0);
    if (old_priority == -1 && errno != 0) {
        perror("getpriority");
        return EXIT_FAILURE;
    }

    printf("Current Priority: %d\n", old_priority);

    // Reduce priority by 10 (i.e., make it "nicer")
    int result = nice(10);
    if (result == -1 && errno != 0) {
        perror("nice");
        return EXIT_FAILURE;
    }

    // Check new priority
    errno = 0;
    new_priority = getpriority(PRIO_PROCESS, 0);
    if (new_priority == -1 && errno != 0) {
        perror("getpriority");
        return EXIT_FAILURE;
    }

    printf("New Priority: %d\n", new_priority);

    // Prepare sleep time: 1,837,272,638 nanoseconds
    struct timespec req = {1, 837272638}; // 1 second + 837,272,638 ns
    printf("Sleeping for %.3f seconds...\n", req.tv_sec + req.tv_nsec / 1e9);

    if (nanosleep(&req, NULL) == -1) {
        perror("nanosleep");
        return EXIT_FAILURE;
    }

    printf("Goodbye! Process finished normally.\n");

    return EXIT_SUCCESS;
}
