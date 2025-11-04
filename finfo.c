/**
 * @file      : finfo.c
 * @brief     : Displays file information using stat() system call.
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


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>

void print_permissions(mode_t mode);
void print_file_type(mode_t mode);

int main(int argc, char *argv[]) {
    struct stat fileStat;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Get file info
    if (stat(argv[1], &fileStat) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    printf("File: %s\n", argv[1]);

    // File type
    print_file_type(fileStat.st_mode);

    // Permissions
    printf("Permissions: ");
    print_permissions(fileStat.st_mode);

    // Owner (UID)
    printf("Owner UID: %d\n", fileStat.st_uid);

    // File size
    printf("File Size: %ld bytes\n", fileStat.st_size);

    // Last modification time
    char mod_time[64];
    struct tm *timeinfo = localtime(&fileStat.st_mtime);
    strftime(mod_time, sizeof(mod_time), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified: %s\n", mod_time);

    return EXIT_SUCCESS;
}

// Helper: print file type
void print_file_type(mode_t mode) {
    printf("File Type: ");
    if (S_ISREG(mode)){
        printf("Regular File\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISCHR(mode)) {
        printf("Character Device\n");
    } else if (S_ISBLK(mode)) {
        printf("Block Device\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO (Pipe)\n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else {
        printf("Unknown\n");
    }                 
}

// Helper: print permissions like rwxr-xr--
void print_permissions(mode_t mode) {
    char perms[10];
    // Make use of ternary operators for simplicity
    perms[0] = (mode & S_IRUSR) ? 'r' : '-';
    perms[1] = (mode & S_IWUSR) ? 'w' : '-';
    perms[2] = (mode & S_IXUSR) ? 'x' : '-';
    perms[3] = (mode & S_IRGRP) ? 'r' : '-';
    perms[4] = (mode & S_IWGRP) ? 'w' : '-';
    perms[5] = (mode & S_IXGRP) ? 'x' : '-';
    perms[6] = (mode & S_IROTH) ? 'r' : '-';
    perms[7] = (mode & S_IWOTH) ? 'w' : '-';
    perms[8] = (mode & S_IXOTH) ? 'x' : '-';
    perms[9] = '\0';

    printf("%s\n", perms);
}