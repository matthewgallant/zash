// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include "open.h"
#include "window.h"

void open_file_to_editor(Editor *editor) {
    FILE *file;
    char ch;

    // Attempt to open the file
    file = fopen(editor->filename, "r");
    if (file != NULL) {
        do {
            // Get char from file
            ch = fgetc(file);

            // Either handle new line or type char
            if (ch == '\n') {
                new_line(editor);
            } else if (ch != EOF) {
                type_character(editor, ch);
            }
        } while (ch != EOF);
    }

    // Cleanup
    fclose(file);
    wrefresh(editor->window);
}
