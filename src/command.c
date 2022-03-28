#include "command.h"
#include "vector.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool check_vector(char* line)
{
    bool first_bracket = false;
    bool last_bracket = false;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == '[') {
            first_bracket = !first_bracket;
            last_bracket = false;
        }
        else if (line[i] == ']' && first_bracket) {
            last_bracket = true;
        }
    }
    return first_bracket && last_bracket;
}


void check_command(char* line)
{
    if (strcmp(line, "quit") == 0 || strcmp(line, "exit") == 0) {
        free(line);
        exit(0);
    }
    else if (strcmp("clc", line) == 0) {
        system("clear");
    }
    else if (check_vector(line)) {
        vector_print(vector_create_from_stdin(line));
    }
    else {
        fprintf(stderr, "Unrecognized function or variable '%s'\n", line);
    }
}