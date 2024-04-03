// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <string.h>

#include "save.h"

void save_to_file(Editor *editor) {
    char line[512];

    // Open file
    FILE *file;
    file = fopen(editor->filename, "w");

    // Loop through lines
    for (int i = 0; i < 512; i++) {
        // Loop through characters
        for (int j = 0; j < 512; j++) {
            // Add character to line
            line[j] = (char)editor->buffer[i][j];
        }

        // If line isn't blank, print to file
        if (line[0] != '\0') {
            fprintf(file, "%s\n", line);
        }

        // Reset line
        memset(line, 0, sizeof(char) * 512);
    }

    // Close when done saving
    fclose(file);
}
