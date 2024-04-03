// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "editor.h"
#include "window.h"
#include "commands.h"
#include "save.h"

int main(int argc, char *argv[]) {
    // Ensure we have a filename
    if (argc != 2) {
        printf("You must pass a filename to Zash!\n");
        return 1;
    }

    // Store application state
    bool quit = false, editorActive = true;
    int maxX, maxY, key;

    // Initialize ncurses
    initscr();
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    getmaxyx(stdscr, maxY, maxX);

    // Create editor data
    Editor editor;
    editor.col = 0, editor.line = 0;
    memset(editor.buffer, 0, sizeof(int) * 512 * 512);
    editor.filename = argv[1];
    editor.window = newwin(maxY - 4, 0, 0, 0);

    // Create commander data
    Editor commander;
    commander.col = 0, commander.line = 0;
    memset(commander.buffer, 0, sizeof(int) * 512 * 512);
    commander.window = newwin(3, 0, maxY - 4, 0);
    
    // Refresh initial screen
    refresh();

    // Create window titles
    update_window_title(&editor, " Editor ");
    update_window_title(&commander, " Commands (esc) ");

    // Create about section
    mvwprintw(stdscr, maxY - 1, 0, "Zash");
    mvwprintw(stdscr, maxY - 1, maxX - 19, "(c) Matthew Gallant");
    
    // Get cursor into initial position
    update_cursor(&editor);

    // Store pointer to active editor
    Editor *activeEditorPtr;
    
    // Main execution loop
    while (!quit) {
        key = getch();

        // Update active editor pointer
        if (editorActive) {
            activeEditorPtr = &editor;
        } else {
            activeEditorPtr = &commander;
        }

        switch (key) {
            case 27:
                switch_windows(&editor, &commander, &editorActive);
                break;
            case KEY_DC:
            case 127:
            case '\b':
                // Only delete if not at edge of screen
                if (activeEditorPtr->col != 0) {
                    activeEditorPtr->col--;
                    type_character(activeEditorPtr, 32);
                    update_cursor(activeEditorPtr);
                }
                break;
            case KEY_ENTER:
            case '\n':
                if (editorActive) {
                    editor.col = 0;
                    move_down(&editor);
                } else {
                    if (process_command(&commander, &editor)) quit = true;
                }
                break;
            case KEY_UP:
                move_up(activeEditorPtr);
                break;
            case KEY_DOWN:
                move_down(activeEditorPtr);
                break;
            case KEY_LEFT:
                move_left(activeEditorPtr);
                break;
            case KEY_RIGHT:
                move_right(activeEditorPtr);
                break;
            default:
                if (key >= 32 && key <= 126) {
                    type_character(activeEditorPtr, key);
                    activeEditorPtr->col++;
                }
                break;
        }

        // Refresh the current window
        wrefresh(activeEditorPtr->window);
    }

    // Clean up before exit
    endwin();
    return 0;
}
