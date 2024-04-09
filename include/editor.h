// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#pragma once

#include <ncurses.h>

typedef struct Editor {
    int col, line, index, bufferSize, bufferLength;
    int *buffer;
    char *filename;
    WINDOW *window;
} Editor;

void initialize_editor(Editor *editor, int bufferSize);

void increment_buffer(Editor *editor);
