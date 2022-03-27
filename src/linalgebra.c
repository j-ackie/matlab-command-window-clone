#include "linalgebra.h"

#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    using_history();

    char* line;
    while ((line = readline(">> ")) != NULL) {
        if (strcmp(line, "quit") == 0) {
            free(line);
            break;
        }
        printf("%s\n", line);
        add_history(line);
        free(line);
    }

    return 0;
}