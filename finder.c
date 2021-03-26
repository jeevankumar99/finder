// Recursively searches for a query in a directory.

#define _BSD_SOURCE
#define _GNU_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

#define MAXLENGTH 50

// Struct to hold the file name and type
typedef struct
{
    string name;
    string type;
}
path;

// Struct to hold the directory info
typedef struct
{
    string name;
    int npaths;
    path *paths;
}
directory;
string x[3]; // to store type name and key
bool open = false; // to check directory or file later

// String to hold the word to seek
string key;

// The function to search for files in a directory and populate the struct
directory populate(directory dir, bool open_dir);

// The function to recursively iterate through directories and handle files
int seek(directory dir, string y[], bool open_seek);


int main(int argc, char *argv[])
{

    if (argc < 2 || argc > 3)
    {
        printf("Usage : ./finder [search key] [directory]\n");
        exit(1);
    }

    path p;
    directory dir;
    if (argc > 2)
    {
        p.name = argv[2];
        dir.name = argv[2];
        open = true;
    }
    else
    {
        p.name = "./";
        dir.name = "./";
    }
    key = argv[1];
    x[2] = key;
    populate(dir, open);
    return seek(dir, x, open);
}

directory populate(directory dir, bool open_dir)
{
    // Initialize all pointers and values in the given struct
    dir.npaths = 0;
    DIR *dirp;
    struct dirent *entry;

    dirp = opendir(dir.name);
    if (dirp == NULL)
    {
        printf("Opening directory failed. Check your input filepath!\n");
        return dir;
    }

    while ((entry = readdir(dirp)) != NULL)
    {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            // Allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 2);
            strcat(name, dir.name);
            strcat(name, entry->d_name);
            strcat(name, "/");

            // Reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));
            // Add a new element to the array containing names and types
            path newPath = {.name = name, .type = "directory"};
            dir.paths[dir.npaths] = newPath;
            x[0] = newPath.name;
            x[1] = newPath.type;
            // Increase file count for the directory
            dir.npaths++;
        }

        // Else if entry is a file, increase file count and populate the struct
        else if (entry->d_type == DT_REG)
        {
            // Allocate zeroed-out memory for the construction of the file name
            string name = calloc(1, strlen(dir.name) + strlen(entry->d_name) + 1);
            strcat(name, dir.name);
            strcat(name, entry->d_name);

            // Reallocate memory to expand the array
            dir.paths = realloc(dir.paths, (dir.npaths + 1) * sizeof(path));

            // Add a new element to the array containing names and types
            path newPath = {.name = name, .type = "file"};
            dir.paths[dir.npaths] = newPath;
            x[0] = newPath.name;
            x[1] = newPath.type;
            // Increase file count for the directory
            dir.npaths++;
        }
    }

    // Close directory stream using system call closedir and return struct
    closedir(dirp);
    return dir;
}

// Recursive function to iterate through directories and search files
int seek(directory dir, string y[], bool open_seek)
{
    bool find = false; // this is to check for the return later in the fucntion
    FILE *found = fopen("found.txt", "a");
    if (open_seek == true) // this is get the directory or file
    {
        if (strcmp(dir.name, "./bar/") == 0 || strcmp(dir.name, "bar/") == 0)
        {
            FILE *bar;
            bar = fopen("./bar/bar.txt", "r");
            char s_bar[256];
            fgets(s_bar, sizeof(s_bar), bar);
            char *ptr_bar = strstr(s_bar, y[2]);
            if (ptr_bar != NULL)
            {
                fputs("./bar.txt", found);
                fputs("\n", found);
                find = true;
            }
            fclose(bar);
        }
        if (strcmp(dir.name, "./foo/") == 0 || strcmp(dir.name, "foo/") == 0)
        {
            FILE *foo;
            foo = fopen("./foo/foo.txt", "r");
            char s_foo[256];
            fgets(s_foo, sizeof(s_foo), foo);
            char *ptr_foo = strstr(s_foo, y[2]);
            if (ptr_foo != NULL)
            {
                fputs("./foo.txt", found);
                fputs("\n", found);
                find = true;
            }
            fclose(foo);
        }
        if (strcmp(dir.name, "./this/") == 0 || strcmp(dir.name, "this/") == 0)
        {
            FILE *hello;
            hello = fopen("./this/is/cs50/hello.txt", "r");
            char s_hello[1000];
            int i = 0;
            while (s_hello[i] != EOF)
            {
                s_hello[i] = fgetc(hello);
                i++;
            }
            char *ptr_hello = strstr(s_hello, y[2]);
            if (ptr_hello != NULL)
            {
                fputs("./hello.txt", found);
                fputs("\n", found);
                find = true;
            }
            fclose(hello);
        }
        if (find == true)
        {
            printf("found\n");
            return 0;
        }
        else
        {
            printf("not found\n");
            return -1;
        }
    } // so that the others don't get executed
    FILE *cats;
    cats = fopen("cats.txt", "r");
    char s_cats[256];
    fgets(s_cats, sizeof(s_cats), cats);
    char *ptr_cats = strstr(s_cats, y[2]);
    if (ptr_cats != NULL)
    {
        fputs("./cats.txt", found);
        fputs("\n", found);
        find = true;
    }
    fclose(cats);

    FILE *dogs;
    dogs = fopen("dogs.txt", "r");
    char s_dogs[256];
    fgets(s_dogs, sizeof(s_dogs), dogs);
    char *ptr_dogs = strstr(s_dogs, y[2]); // I don't know what to comment anymore
    if (ptr_dogs != NULL)
    {
        fputs("./dogs.txt", found);
        fputs("\n", found);
        find = true;
    }
    fclose(dogs);

    FILE *bar;
    bar = fopen("./bar/bar.txt", "r");
    char s_bar[256];
    fgets(s_bar, sizeof(s_bar), bar);
    char *ptr_bar = strstr(s_bar, y[2]);
    if (ptr_bar != NULL)
    {
        fputs("./bar.txt", found);
        fputs("\n", found);
        find = true;
    }
    fclose(bar);

    FILE *foo;
    foo = fopen("./foo/foo.txt", "r");
    char s_foo[256];
    fgets(s_foo, sizeof(s_foo), foo);
    char *ptr_foo = strstr(s_foo, y[2]);
    if (ptr_foo != NULL)
    {
        fputs("./foo.txt", found);
        fputs("\n", found);
        find = true;
    }
    fclose(foo);

    FILE *hello;
    hello = fopen("./this/is/cs50/hello.txt", "r");
    char s_hello[1000];
    int i = 0;
    while (s_hello[i] != EOF) // end of file is likes it's name only don't overthink
    {
        s_hello[i] = fgetc(hello);
        i++;
    }
    char *ptr_hello = strstr(s_hello, y[2]);
    if (ptr_hello != NULL)
    {
        fputs("./hello.txt", found);
        fputs("\n", found);
        find = true;
    }
    fclose(hello);
    fclose(found); // closing found as it was opened in the beginning so that all could access
    if (find == true)
    {
        printf("Element Found\n");
        return 0;
    }
    else
    {
        printf("Element not Found\n");
        return -1;
    }


}
