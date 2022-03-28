#include "linalgebra.h"
#include "util.h"
#include "command.h"

#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    using_history();

    char* line;
    while ((line = readline(">> ")) != NULL) {
        strip(line);
        check_command(line);
        add_history(line);
        free(line);
    }
    return 0;
}