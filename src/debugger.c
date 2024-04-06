// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <string.h>

#include "debugger.h"
#include "window.h"

void refresh_debugger(Editor *debugger, Editor *editor) {
    char buf[17]; // 16 chars + end of string char

    // Clear and reset window
    werase(debugger->window);
    update_window_title(debugger, " Debugger ");

    // Print index
    snprintf(buf, sizeof(buf), "%s%d", "index: ", editor->index);
    mvwprintw(debugger->window, 1, 1, buf);

    // Print line
    snprintf(buf, sizeof(buf), "%s%d", "line: ", editor->line);
    mvwprintw(debugger->window, 2, 1, buf);

    // Print col
    snprintf(buf, sizeof(buf), "%s%d", "col: ", editor->col);
    mvwprintw(debugger->window, 3, 1, buf);

    // Print buffer size
    snprintf(buf, sizeof(buf), "%s%d", "buff size: ", editor->bufferSize);
    mvwprintw(debugger->window, 4, 1, buf);

    // Print buffer
    mvwprintw(debugger->window, 6, 1, "     BUFFER     ");

    attron(COLOR_PAIR(1));

    // Store pointer to current character
    int *curCharPtr;

    // Loop through first 16 rows (256 chars)
    for (int i = 0; i < 16; i++) {
        // Reset buffer
        memset(buf, 0, 16);

        // Loop through cols
        for (int j = 0; j < 16; j++) {
            // Set current character
            curCharPtr = &editor->buffer[i * 16 + j];

            // Only print real characters
            if (*curCharPtr != 0) {
                if (*curCharPtr == 10) {
                    // Newlines
                    buf[j] = '\\';
                } else {
                    buf[j] = (char)*curCharPtr;
                }
            } else {
                buf[j] = (char)32;
            }
        }

        // Null-terminate string
        buf[16] = '\0';

        // Print 16 character buffer to window
        mvwprintw(debugger->window, 7 + i, 1, buf);
    }
    
    wrefresh(debugger->window);
}
