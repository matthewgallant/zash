// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <stdlib.h>

#include "window.h"

void update_cursor(Editor *editor) {
    wmove(editor->window, editor->line, editor->col);
}

void type_character(Editor *editor, int character) {
    // TODO: Shift remaining chars in line up
    mvwaddch(editor->window, editor->line, editor->col, (char)character);
    
    // Update buffer size if needed and add char to it
    increment_buffer(editor);
    editor->buffer[editor->index] = character;
    editor->bufferLength++;
    
    // Update cursor properties
    editor->col++;
    editor->index++;
}

void delete_character(Editor *editor) {
    // Only delete if not at edge of screen
    if (editor->col > 1) {
        // TODO: Shift remaining chars in line down
        editor->buffer[editor->index - 1] = 0;
        editor->col--;
        editor->index--;
        mvwaddch(editor->window, editor->line, editor->col, 32);
        update_cursor(editor);
    }
}

void new_line(Editor *editor) {
    // Update buffer size and add new line char
    increment_buffer(editor);
    editor->buffer[editor->index] = 10;
    editor->bufferLength++;

    // Update cursor properties
    editor->line++;
    editor->index++;

    // Move cursor to next line
    editor->col = 1;
    move_down(editor);
}

void move_up(Editor *editor) {
    // Check if user can move further up
    if (editor->line > 1) {
        editor->line--;

        // Loop to top of previous line twice
        for (int i = 0; i < 2; i++) {
            while (editor->buffer[editor->index - 1] != 10 && editor->index > 1) editor->index--;
            if (editor->index > 0) editor->index--;
        }

        // Account for the beginning of the buffer
        if (editor->index == 0) {
            editor->index--;
        }

        // Either reach column or new line char
        for (int i = 0; i < editor->col; i++) {
            editor->index++;
            if (editor->buffer[editor->index] == 10) {
                editor->col = i + 1;
                break;
            }
        }
        
        update_cursor(editor);
    }
}

void move_down(Editor *editor) {
    int prevIndex = editor->index;

    // Loop to next line
    while (editor->buffer[editor->index + 1] != 0 && editor->buffer[editor->index + 1] != 10) editor->index++;
    editor->index++;

    // Check we're not at the end of the file
    if (editor->buffer[editor->index] != 0) {
        editor->line++;

        // Either reach column or new line char
        for (int i = 1; i < editor->col; i++) {
            editor->index++;

            // End of line, move cursor here
            if (editor->buffer[editor->index] == 10 || editor->buffer[editor->index] == 0) {
                editor->col = i;
                break;
            }

            // Partway through line, move cursor here
            if (i + 1 == editor->col) {
                editor->index++;
                break;
            }
        }
    } else {
        // Reset index if we don't find a new line
        editor->index = prevIndex;
    }
    
    update_cursor(editor);
}

void move_left(Editor *editor) {
    // Check if user can move further left
    if (editor->col > 1) {
        editor->col--;
        editor->index--;
        update_cursor(editor);
    }
}

void move_right(Editor *editor) {
    // Check if user can move further right
    if (editor->buffer[editor->index] != 0 && editor->buffer[editor->index] != 10) {
        editor->col++;
        editor->index++;
        update_cursor(editor);
    }
}

void update_window_title(Editor *editor, char *title) {
    box(editor->window, 0, 0);
    mvwprintw(editor->window, 0, 1, title);
    wrefresh(editor->window);
}

void switch_windows(Editor *editor, Editor *commander, bool *editorActive) {
    if (*editorActive) {
        *editorActive = false;
        update_window_title(editor, " Editor (F1) ");
        update_window_title(commander, " Commands ");
        update_cursor(commander);
    } else {
        *editorActive = true;
        update_window_title(editor, " Editor ");
        update_window_title(commander, " Commands (F1) ");
        update_cursor(editor);
    }
}
