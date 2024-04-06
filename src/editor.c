// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <stdlib.h>

#include "editor.h"

void initialize_editor(Editor *editor, int bufferSize) {
    editor->col = 1;
    editor->line = 1;
    editor->index = 0;
    editor->bufferSize = bufferSize;
    editor->buffer = (int*)calloc(bufferSize, sizeof(int));
    
    if (editor->buffer == NULL) {
        endwin();
        printf("Unable to allocate memory for editor.\n");
        exit(1);
    }
}
