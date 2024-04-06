// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include "window.h"

void update_cursor(Editor *editor) {
    wmove(editor->window, editor->line, editor->col);
}

void type_character(Editor *editor, int character) {
    mvwaddch(editor->window, editor->line, editor->col, (char)character);
    editor->buffer[editor->index] = character;
    editor->col++;
    editor->index++;
}

void delete_character(Editor *editor) {
    // Only delete if not at edge of screen
    if (editor->col > 1) {
        editor->buffer[editor->index - 1] = 0;
        editor->col--;
        editor->index--;
        
        // TODO: Shift remaining chars in line down instead
        mvwaddch(editor->window, editor->line, editor->col, 32);

        update_cursor(editor);
    }
}

void new_line(Editor *editor) {
    // Insert new line char into buffer and update index
    editor->buffer[editor->index] = 10;
    editor->index++;

    // Move cursor to next line
    editor->col = 1;
    move_down(editor);
}

void move_up(Editor *editor) {
    // TODO: move column to left if line below is shorter
    // TODO: Update index accordingly
    // Check if user can move further up
    if (editor->line > 1) {
        editor->line--;
        update_cursor(editor);
    }
}

void move_down(Editor *editor) {
    // TODO: move column to left if line below is shorter
    // TODO: Update index accordingly
    // TODO: Check if user can move further down
    editor->line++;
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
        update_window_title(editor, " Editor (esc) ");
        update_window_title(commander, " Commands ");
        update_cursor(commander);
    } else {
        *editorActive = true;
        update_window_title(editor, " Editor ");
        update_window_title(commander, " Commands (esc) ");
        update_cursor(editor);
    }
}
