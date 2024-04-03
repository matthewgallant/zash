// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <string.h>

#include "commands.h"
#include "save.h"

bool process_command(Editor *commander, Editor *editor) {
    // Allocate memory for the C string
    char command[512];

    // Convert each integer to its corresponding ASCII character
    for (int i = 0; i < 512; i++) {
        // Ignore spaces in command
        if (commander->buffer[0][i] != 32) {
            command[i] = (char)commander->buffer[0][i];
        }
    }

    // Parse commands
    if (strcmp(command, "sq") == 0) {
        save_to_file(editor);
        return true;
    } else if (strcmp(command, "s") == 0) {
        save_to_file(editor);
    } else if (strcmp(command, "q") == 0) {
        return true;
    }
    
    return false;
}
