#include "util.h"

#include <stdio.h>
#include "string.h"
#include "ctype.h"

void lstrip(char* line)
{
    int i = 0;
    while (isspace(line[i]) != 0) {
        i++;
    }
    memmove(line, line + i, strlen(line) + 1 - i);
}

void rstrip(char* line)
{
    int i = strlen(line) - 1;
    while (isspace(line[i]) != 0 && i >= 0) {
        i--;
    }
    line[i + 1] = '\0';
}


void strip(char* line)
{
    lstrip(line);
    rstrip(line);
}


bool check_quit(char* line)
{
    return strcmp(line, "quit") == 0 || strcmp(line, "exit") == 0;
}
