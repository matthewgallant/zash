// Zash
// A wicked fast command-line text editor written in pure C.
// (c) 2024 Matthew Gallant

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "editor.h"
#include "window.h"
#include "commands.h"
#include "open.h"
#include "save.h"
#include "debugger.h"

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
    initialize_editor(&editor, 512);
    editor.filename = argv[1];
    editor.window = newwin(maxY - 4, maxX - 35, 0, 0);

    // Create commander data
    Editor commander;
    initialize_editor(&commander, 128);
    commander.window = newwin(3, maxX - 35, maxY - 4, 0);

    // Create debugger window
    Editor debugger;
    initialize_editor(&debugger, 256);
    debugger.window = newwin(maxY - 1, 34, 0, maxX - 35);
    
    // Refresh initial screen
    refresh();

    // Create window titles
    update_window_title(&editor, " Editor ");
    update_window_title(&commander, " Commands (F1) ");
    update_window_title(&debugger, " Debugger ");

    // Create about section
    mvwprintw(stdscr, maxY - 1, 0, "Zash");
    mvwprintw(stdscr, maxY - 1, maxX - 19, "(c) Matthew Gallant");

    // Read file if exists
    if (editor.filename != NULL) {
        open_file_to_editor(&editor);
    }

    // Get cursor into initial position
    update_cursor(&editor);
    refresh_debugger(&debugger, &editor);

    // Store pointer to active editor
    Editor *activeEditorPtr;

    // Main execution loop
    while (!quit) {

        // Only run when a key is pressed
        if ((key = getch()) != ERR) {
            
            // Update active editor pointer
            if (editorActive) {
                activeEditorPtr = &editor;
            } else {
                activeEditorPtr = &commander;
            }

            // Primary logic switch
            switch (key) {
                case KEY_F(1):
                    switch_windows(&editor, &commander, &editorActive);
                    break;
                case KEY_DC:
                case 127:
                case '\b':
                    delete_character(activeEditorPtr);
                    break;
                case KEY_ENTER:
                case '\n':
                    if (editorActive) {
                        new_line(&editor);
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
                    }
                    break;
            }

            // Refresh the windows
            refresh_debugger(&debugger, &editor);
            wrefresh(activeEditorPtr->window);
        }
    }

    // Clean up before exit
    endwin();
    return 0;
}
