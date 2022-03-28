#pragma once

#include "stdbool.h"

void lstrip(char* line);

void rstrip(char* line);

void strip(char* line);

// Returns true if user inputs "quit" or "exit"
// Precondition: line has been stripped
bool check_quit(char* line);