/**
 * @file      : pinfo.c
 * @brief     : Displays process information (priority, scheduling policy).
 * 
 * Author     : Jesse Rost <rostj@msoe.edu>
 * Date       : 11/02/25
 * Course     : CPE 2600
 * Section    : 112
 * Assignment : Lab 9
 * Algorithm  :
 *  - Check if a PID is provided on the command line
 *      - If none is provided, use the current process ID
 *  - Retrieve the process's scheduling policy using sched_getscheduler()
 *  - Retrieve the process priority using getpriority()
 *  - Display the PID, priority, and human-readable scheduling
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <string.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    int priority, policy;

    // Determine PID: either from command line or current process
    if (argc == 1) {
        pid = getpid();
    } else if (argc == 2) {
        pid = (pid_t) atoi(argv[1]);
    } else {
        fprintf(stderr, "Usage: %s [pid]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Get scheduling policy
    policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("sched_getscheduler");
        return EXIT_FAILURE;
    }

    // Get priority
    errno = 0;
    priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        perror("getpriority");
        return EXIT_FAILURE;
    }

    // Print info
    printf("Process ID        : %d\n", pid);
    printf("Process Priority  : %d\n", priority);
    printf("Scheduling Policy : ");

    switch (policy) {
        case SCHED_OTHER:   
            printf("SCHED_OTHER (Normal)\n"); 
            break;
        case SCHED_FIFO:    
            printf("SCHED_FIFO (Real-time, FIFO)\n"); 
            break;
        case SCHED_RR:      
            printf("SCHED_RR (Real-time, Round Robin)\n"); 
            break;
// SCHED_BATCH is a Linux-specific scheduling policy.
// This case is conditionally compiled only if SCHED_BATCH is defined
// to ensure portability on systems that do not support it.
#ifdef SCHED_BATCH
        case SCHED_BATCH:   
            printf("SCHED_BATCH (Batch)\n"); 
            break;
#endif
// SCHED_IDLE is also a Linux-specific scheduling policy.
// Guarded with #ifdef to prevent compilation errors on non-Linux systems
// where this constant may not exist.
#ifdef SCHED_IDLE
        case SCHED_IDLE:    
            printf("SCHED_IDLE (Idle)\n"); 
            break;
#endif
        default:            
            printf("Unknown Policy (%d)\n", policy); 
            break;
    }

    return EXIT_SUCCESS;
}