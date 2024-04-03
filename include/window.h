// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#pragma once

#include "editor.h"

void update_cursor(Editor *editor);

void type_character(Editor *editor, int character);

void move_up(Editor *editor);

void move_down(Editor *editor);

void move_left(Editor *editor);

void move_right(Editor *editor);

void update_window_title(Editor *editor, char *title);

void switch_windows(Editor *editor, Editor *commander, bool *editorActive);
