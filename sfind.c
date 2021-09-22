#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "sfind.h"
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>


char *substring;
char *ret;
bool fileT = true;
bool symLink = false;

/*
   Pre-conditons: User has given the file type they would like to filter files by
   , or user has given no file type meaning no files have to be filtered.
   Post-conditons: Sets bool to true if given file is the file type that the
   user specified. Otherwise, if the file type option is not available, it exitsx
   Parameters:
   struct stat c - holds the mode of the file
   char fileType[] - holds the file type that user wants to filter for
   Return: void
*/
void checkFile(struct stat c, char fileType[]) {
    fileT = false;
    symLink = false;
    switch(c.st_mode & S_IFMT) {
    case S_IFBLK:
    {
        if (fileType[0] == 'b') {
            fileT = true;
        }
        break;
    }
    case S_IFCHR:
    {
        if (fileType[0] == 'c') {
            fileT = true;
        }
        break;
    }
    case S_IFDIR:
    {
        if (fileType[0] == 'd') {
            fileT = true;
        }
        break;
    }
    case S_IFIFO:
    {
        if (fileType[0] == 'p') {
            fileT = true;
        }
        break;
    }
    case S_IFREG:
    {
        if (fileType[0] == 'f') {
            fileT = true;
        }
        break;
    }
    case S_IFLNK:
    {
        if (fileType[0] == 'l') {
            fileT = true;
            symLink = true;
        }
        break;
    }
    case S_IFSOCK:

    {
        if (fileType[0] == 's') {
            fileT = true;
        }
        break;
    }
    default:
    {
        {
        printf("\nNo such filetype.");
        exit(1);
        break;
        }
    }
    }
    if (fileType[0] == 'a') {
        fileT = true;
    }
}

/*
  Pre-conditons: Directory exists and is not NULL
  Post-conditons: Searches directory for files that include the substring and meet
  the file type criterion. Then it prints the absolute path of the files that meet
  the criterion.
  Parameters:
  char dirname[] -  name of the directory inputted
  char *substrings - substring that should be included in the files printed
  char fileType[] - file type char that user wants to be filtered in
  Return: void
*/
void searchdir(char dirname[], char *substrings, char fileType[]) {
    char path[1000];
    char cwd[1000];
    struct dirent *myfile;
    DIR *dir = opendir(dirname);
    struct stat mystat;
    int n;
    n = 0;
    //Unable to open directory stream
    if (!dir)
        return;

    chdir(dirname);
    while (((myfile = readdir(dir)) != NULL) && dir)
    {
        n = lstat(myfile->d_name, &mystat);

        if (strcmp(myfile->d_name, ".") != 0 && strcmp(myfile->d_name, "..") != 0 && n != -1)
        {
            // finds if substring is within file name
            if (substrings != NULL) {
            ret = strstr(myfile->d_name, substrings);
            }
            //gets absolute path of file
            char buf[PATH_MAX + 1];
            char *res = realpath(myfile->d_name, buf);
            checkFile(mystat, fileType);
            if ((ret != NULL && fileT == true && symLink == false) ||
            (fileT == true && substrings == NULL && symLink == false)) {
                printf("%s\n", buf);
            }

            if ((symLink == true && ret!= NULL && fileT == true) ||
            (symLink == true && fileT == true && substring == NULL)) {
                getcwd(cwd, sizeof(cwd));
                strcat(cwd, "/");
                strcat(cwd, myfile->d_name);
                printf("%s\n", cwd);
            }

            // copies path of file to see check if it is a directory calls the function recursively
            strcpy(path, dirname);
            strcat(path, "/");
            strcat(path, myfile->d_name);
            searchdir(path, substrings, fileType);

        }
    }

    // Changes directory to parent directory and closes directory stream
    chdir("..");
    closedir(dir);
}

/*
   Pre-conditons: N/A
   Post-conditons: Takes in comman line argument to call searchdir()
   and also checks if given dir is not NULL and exists.
   Parameters: int argc, char* argv
   Return: 0
*/
int main(int argc, char* argv[]) {
    char dirname[1000] = ".";
    DIR *mydir;
    char ch = ' ';
    char fileType[20];
    fileType[0] = 'a';

    if(argc > 1) {
        if(strcmp(argv[1], "-n") == 0) {
            strcpy(dirname, ".");
        } else {
        strcpy(dirname, argv[1]);
        }
    }

    if (argc < 2) {
        printf("Not enough commandline arguments.\n");
        return 1;
    }

    while ((ch = getopt(argc, argv, ":n:t:")) != EOF) {
        switch(ch) {
        case 'n':
        {
            substring = optarg;
            break;
        }
        case 't':
        {
            strcpy(fileType, optarg);
            break;
        }
        case '?':
        {
            default:
            {
                printf("%s", optarg);
                fprintf(stderr, "Unrecognized input.\n");
                exit(1);
                break ;
            }

        }
        }
    }

    if(!isdirectory(dirname)) {
        fprintf(stderr, "This is not a directory.\n");
        return 1;
    }
    mydir = opendir(dirname);
    if(mydir == NULL) {
      perror("Directory is null.\n");
      return 1;
    }

    closedir(mydir);

    searchdir(dirname ,substring, fileType);

    return 0;
}
