#include <ncurses.h>

int main() {
    initscr(); // Initialize Ncurses
    noecho();  // Disable automatic echoing of typed characters
    cbreak();  // Disable line buffering (characters are available immediately)
    curs_set(0); // Hide the cursor

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    // Check if the terminal is large enough to create a 720p window
    if (max_y < 720 || max_x < 1280) {
        endwin(); // Close Ncurses
        printf("Terminal is too small for 720p resolution.\n");
        return 1;
    }

    // Create a "virtual window" with 720p resolution
    WINDOW *hd_window = newwin(720, 1280, 0, 0);

    // Enable scrolling if the content exceeds the window size
    scrollok(hd_window, TRUE);

    // Print some content in the 720p window
    wprintw(hd_window, "Hello, 720p World!\n");
    wrefresh(hd_window);

    // Wait for a key press before exiting
    getch();

    // Clean up
    delwin(hd_window);
    endwin();

    return 0;
}
