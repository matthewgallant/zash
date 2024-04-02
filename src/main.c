// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "editor.h"
#include "window.h"
#include "save.h"

int main(int argc, char *argv[]) {
    // Ensure we have a filename
    if (argc != 2) {
        printf("You must pass a filename to Zash!\n");
        return 1;
    }

    // Store quit state
    bool quit = false;

    // Initialize ncurses
    initscr();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    // Create editor data
    Editor editor;
    editor.curX = 1;
    editor.curY = 1;
    editor.window = newwin(0, 0, 0, 0);
    memset(editor.buffer, 0, sizeof(int) * 1024 * 1024);
    
    // Draw editor window
    refresh();
    box(editor.window, 0, 0);
    mvwprintw(editor.window, 0, 1, "Editor");
    update_cursor(&editor);
    wrefresh(editor.window);
    
    // Main execution loop
    while (!quit) {
        editor.key = getch();

        if (editor.key == 27) {
            // Save file and quit (esc)
            save_to_file(&editor, argv[1]);
            quit = TRUE;
        } else if (editor.key == KEY_DC || editor.key == 127 || editor.key == '\b') {
            // Only delete if not at edge of screen
            if (editor.curX != 1) {
                editor.curX--;
                type_character(&editor, 32);
                update_cursor(&editor);
            }
        } else if (editor.key == KEY_ENTER || editor.key == '\n') {
            // Handle enter
            editor.curX = 1;
            move_down(&editor);
        } else if (editor.key == KEY_UP) {
            move_up(&editor);
        } else if (editor.key == KEY_DOWN) {
            move_down(&editor);
        } else if (editor.key == KEY_LEFT) {
            move_left(&editor);
        } else if (editor.key == KEY_RIGHT) {
            move_right(&editor);
        } else if (editor.key >= 32 && editor.key <= 126) {
            // Handle generic typing
            type_character(&editor, editor.key);
            editor.curX++;
        }

        // Refresh the editor window
        wrefresh(editor.window);
    }

    // Clean up before exit
    endwin();
    return 0;
}
