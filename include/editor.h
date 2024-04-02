// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#pragma once

#include <ncurses.h>

typedef struct Editor {
    int key;
    int curX;
    int curY;
    WINDOW *window;
    int buffer[1024][1024];
} Editor;
