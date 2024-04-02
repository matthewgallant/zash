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
    editor.curX = 0;
    editor.curY = 0;
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

        switch (editor.key) {
            case 27:
                // Save file and quit (esc)
                save_to_file(&editor, argv[1]);
                quit = TRUE;
                break;
            case KEY_DC:
            case 127:
            case '\b':
                // Only delete if not at edge of screen
                if (editor.curX != 0) {
                    editor.curX--;
                    type_character(&editor, 32);
                    update_cursor(&editor);
                }
                break;
            case KEY_ENTER:
            case '\n':
                editor.curX = 0;
                move_down(&editor);
                break;
            case KEY_UP:
                move_up(&editor);
                break;
            case KEY_DOWN:
                move_down(&editor);
                break;
            case KEY_LEFT:
                move_left(&editor);
                break;
            case KEY_RIGHT:
                move_right(&editor);
                break;
            default:
                if (editor.key >= 32 && editor.key <= 126) {
                    type_character(&editor, editor.key);
                    editor.curX++;
                }
                break;
        }

        // Refresh the editor window
        wrefresh(editor.window);
    }

    // Clean up before exit
    endwin();
    return 0;
}
