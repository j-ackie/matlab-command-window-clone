#include "command.h"
#include "vector.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ans
{
    void* val;
};

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

bool check_assignment(char* line)
{
    if (strcmp(line, "") != 0) {
        if ((line[0] >= 65 && line[0] <= 90) || (line[0] >= 97 && line[0] <= 122)) {
            bool numeric = false;
            bool equals_sign = false;
            int equals_sign_index = 0;
            for (int i = 1; line[i] != '\0'; i++) {
                if (line[i] == '=' && !equals_sign) {
                    equals_sign = true;
                    equals_sign_index = i;
                }
                else if (line[i] == '=' && equals_sign) {
                    equals_sign = false;
                }
                else if (line[i] >= 48 && line[i] <= 57 && equals_sign) {
                    numeric = true;
                }
            }
            if (numeric) {
                char subtext[strlen(line) + 1 - equals_sign_index];
            }           
        }
    }
    
}

void check_command(char* line)
{
    void* ans;
    if (strcmp(line, "quit") == 0 || strcmp(line, "exit") == 0) {
        free(line);
        exit(0);
    }
    else if (strcmp("clc", line) == 0) {
        system("clear");
    }
    else if (check_vector(line)) {
        ans = vector_create_from_stdin(line);
        if (ans != NULL) {
            vector_print(ans);
        }
    }
    else {
        fprintf(stderr, "Unrecognized function or variable '%s'.\n", line);
    }
}