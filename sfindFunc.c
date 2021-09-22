#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


 /*
    Pre-conditons: Directory must be given by user in as a commandline argument
    Post-conditons: Checks to see if such a file exists, and if such file exists,
    it checks to see it the file is a directory.
    it is possible to
    Parameters: char filename[] - name of given directory
    Return: int - if 0, then not a directory, if 1, sucessful
*/

int isdirectory(char filename[]) {
    int err;
    struct stat mystat;
    err = stat(filename, &mystat);
    if(err == -1) {
        if(ENOENT == errno) {
            return 0;
        } else {
            perror("stat");
            exit(1);
        }
    } else {
        if(S_ISDIR(mystat.st_mode)) {
            return 1;
        } else {
            fprintf(stderr, "ls: %s: No such file in directory", filename);
            return 0;
        }
    }

}
