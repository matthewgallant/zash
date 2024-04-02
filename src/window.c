// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include "window.h"

void update_cursor(Editor *editor) {
    wmove(editor->window, editor->curY, editor->curX);
}

void type_character(Editor *editor, int character) {
    mvwaddch(editor->window, editor->curY, editor->curX, (char)character);
    editor->buffer[editor->curY - 1][editor->curX - 1] = character;
}

void move_up(Editor *editor) {
    editor->curY--;
    update_cursor(editor);
}

void move_down(Editor *editor) {
    editor->curY++;
    update_cursor(editor);
}

void move_left(Editor *editor) {
    editor->curX--;
    update_cursor(editor);
}

void move_right(Editor *editor) {
    update_cursor(editor);
}
