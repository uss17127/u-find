Program: sfind.c sfinfFunc.c

----------------------------------------------------------------------------------
The sfind program mimics the find command in unix. It prints out the absolute
path of files that meet the criterion of including the substring within the file
name as well as being the type of file that the user specified.
----------------------------------------------------------------------------------
Input Parameters:

--- in sfind.c
- checkfile - struct stat c, char fileType
- searchdir - char dirname[], char *substrings, char fileType[]

--- in sfindFunc.c
- isdirectory - char filename[]

----------------------------------------------------------------------------------
Expected Output:

--- in sfind.c
- checkfile - void
- searchdire - void
--- in sfindFunc.c
- isdirectory - int
----------------------------------------------------------------------------------

CODER: Urja Shah
CREDIT/CONTRIBUTION:
- cobweb P3 instructions
- isdirectory from Lab07

How to compile:
gcc -g -Wall sfind.c sfindFunc.c -o sfind

OR use Makefile:
   make - to compile
   make clean - to clean
How to run:
    sfind <directory-where to start looking> -n substring-criteria -t <filetype>
    or
    sfind <directory-where to start looking> -n substring-criteria
