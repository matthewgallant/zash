// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <string.h>

#include "debugger.h"
#include "window.h"

void refresh_debugger(Editor *debugger, Editor *editor) {
    char buf[33]; // 32 chars + end of string char

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
    snprintf(buf, sizeof(buf), "%s%d", "bufferSize: ", editor->bufferSize);
    mvwprintw(debugger->window, 4, 1, buf);

    // Print buffer length
    snprintf(buf, sizeof(buf), "%s%d", "bufferLength: ", editor->bufferLength);
    mvwprintw(debugger->window, 5, 1, buf);

    attron(COLOR_PAIR(1));

    // Store pointer to current character
    int *curCharPtr;

    // Loop through buffer size
    for (int i = 0; i < editor->bufferSize / 32; i++) {
        // Reset buffer
        memset(buf, 0, 32);

        // Loop through cols
        for (int j = 0; j < 32; j++) {
            // Set current character
            curCharPtr = &editor->buffer[i * 32 + j];

            // Only print real characters
            if (*curCharPtr != 0) {
                if (*curCharPtr == 10) {
                    // Newlines
                    buf[j] = '\\';
                } else {
                    buf[j] = (char)*curCharPtr;
                }
            } else {
                buf[j] = '0';
            }
        }

        // Null-terminate string
        buf[32] = '\0';

        // Print 16 character buffer to window
        mvwprintw(debugger->window, 6 + i, 1, buf);
    }
    
    wrefresh(debugger->window);
}
