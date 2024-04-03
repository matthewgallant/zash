// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#pragma once

#include <ncurses.h>

typedef struct Editor {
    int col, line;
    int buffer[512][512];
    char *filename;
    WINDOW *window;
} Editor;
