// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <stdlib.h>

#include "editor.h"
#include "window.h"

void initialize_editor(Editor *editor, int bufferSize) {
    editor->col = 1;
    editor->line = 1;
    editor->index = 0;
    editor->bufferSize = bufferSize;
    editor->bufferLength = 0;
    editor->buffer = (int*)calloc(bufferSize, sizeof(int));
    
    if (editor->buffer == NULL) {
        endwin();
        printf("Unable to allocate memory for editor window.\n");
        exit(1);
    }
}

void increment_buffer(Editor *editor) {
    int *backupBuffer = editor->buffer;

    if (editor->bufferLength == editor->bufferSize) {
        // Increase buffer size via reallocation
        editor->buffer = realloc(editor->buffer, editor->bufferSize + 512 * sizeof(int));

        // Check for reallocation
        if (editor->buffer == NULL) {
            // Can't get more memory, restore original buffer
            editor->buffer = backupBuffer;

            // TODO: Update to use status area
            update_window_title(editor, " Unable to allocate more memory. Please save your file. ");
        } else {
            editor->bufferSize += 512;
        }
    }
}
