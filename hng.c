#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

int n = 0;

int check_char(char *word, int length, char c, WINDOW *win) {
    int check = 0;
    for (int i = 0; i < length; i++) {
        if (c == word[i]) {
            mvwprintw(win, 8, 5 + i, "%c", c);
            n += 1;
            check = 1;
        }
    }
    if (check == 0) {
        return -1;
    } else {
        wrefresh(win);
        return 0;
    }
}

void render_hng(int count, WINDOW *win) {
    int i;
    for (int i = 0; i < 4; i++) {
        mvwprintw(win, 2, i + 5,  "_");
    }
    mvwprintw(win, 3, 4, "|");
    for (int i = 0; i < 4; i++) {
        mvwprintw(win, 3 + i, 9, "|");
    }
    for (int i = 0; i < 3; i++) {
        mvwprintw(win, 7, i + 8, "-");
    }
    mvwprintw(win, 4, 4, "O");
    if (count >= 1) {
        mvwprintw(win, 5, 4, "|");
        if (count >= 2) {
            mvwprintw(win, 5, 3, "-");
            if (count >= 3) {
                mvwprintw(win, 5, 5, "-");
                if (count >= 4) {
                    mvwprintw(win, 6, 3, "/");
                    if (count >= 5) {
                        mvwprintw(win, 6, 5, "\\");
                    }
                }
            }
        }
    }
}

void render_word(char *word, int length, WINDOW *win) {
   for (int i = 0; i < length; i++) {
       if (word[i] == word[0] || word[i] == word[length - 1]) {
           mvwprintw(win, 8, 5 + i, "%c", word[i]);
           n += 1;
       } else {
           mvwprintw(win, 8, 5 + i, "_");
       }
   }
}

int main(int argc, char* argv[]) {
    
    char word[50];
    initscr();


    WINDOW *win;
    win = newwin(20, 40, 1, 1);

    box(win, 0, 0);
    wrefresh(win);
    curs_set(0);
    scanf("%s", word);
    int length = strlen(word);
    int count = 0;
    render_word(word, length, win);
    wrefresh(win);
    render_hng(count, win);
    wrefresh(win);
    
    bool loop = TRUE;
    char c;
    int check;
    while(loop) {
        c = getchar();
        check = check_char(word, length, c, win);
        if (check == -1) {
            render_hng(count, win);
            count++;
            wrefresh(win);
        }
        if (count > 6 || n == length) {
            sleep(2);
            loop = FALSE;
        }
    }

    endwin();

    return 0;
}