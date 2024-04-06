// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <string.h>

#include "save.h"

void save_to_file(Editor *editor) {
    char contents[editor->bufferSize];

    // Open file
    FILE *file;
    file = fopen(editor->filename, "w");

    // Loop through lines
    for (int i = 0; i < editor->bufferSize; i++) {
        contents[i] = (char)editor->buffer[i];
    }

    // If line isn't blank, print to file
    if (contents[0] != '\0') {
        fprintf(file, "%s", contents);
    }

    // Close when done saving
    fclose(file);
}
