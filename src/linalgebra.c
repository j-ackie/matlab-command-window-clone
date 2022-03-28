#include "linalgebra.h"
#include "util.h"

#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    using_history();

    char* line;
    while ((line = readline(">> ")) != NULL) {
        strip(line);
        if (check_quit(line)) {
            free(line);
            break;
        }
        printf("%s\n", line);
        add_history(line);
        free(line);
    }
    return 0;
}