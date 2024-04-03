// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include "window.h"

void update_cursor(Editor *editor) {
    wmove(editor->window, editor->line + 1, editor->col + 1);
}

void type_character(Editor *editor, int character) {
    mvwaddch(editor->window, editor->line + 1, editor->col + 1, (char)character);
    editor->buffer[editor->line][editor->col] = character;
}

void move_up(Editor *editor) {
    editor->line--;
    update_cursor(editor);
}

void move_down(Editor *editor) {
    editor->line++;
    update_cursor(editor);
}

void move_left(Editor *editor) {
    editor->col--;
    update_cursor(editor);
}

void move_right(Editor *editor) {
    update_cursor(editor);
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
