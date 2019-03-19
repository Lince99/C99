#include <ncurses.h>
#include <stdlib.h>

typedef struct QUEUE_CHAR queue_char;

struct QUEUE_CHAR {
    char value;
    queue_char* next;
};

queue_char* initQueue_char(char val) {
    queue_char* node = NULL;

    node = (queue_char*) malloc(sizeof(queue_char));
    if(node == NULL) {
        perror("Error adding element to queue!\n");
        return NULL;
    }
    node->value = val;
    node->next = NULL;

    return node;
}

queue_char* pushQueue_char(queue_char* q, char val) {
    queue_char* node = NULL;
    queue_char* head = q;

    node = initQueue_char(val);
    if(q == NULL)
        return node;
    while(q->next != NULL)
        q = q->next;
    q->next = node;

    return head;
}

queue_char* popQueue_char(queue_char* q) {
    queue_char* head = q;
    queue_char* prev = NULL;

    if(q == NULL)
        return NULL;
    while(q->next != NULL) {
        prev = q;
        q = q->next;
    }
    if(prev == NULL)
        return NULL;
    prev->next = NULL;

    return head;
}

char getLastQueue_char(queue_char* q) {

    if(q == NULL)
        return 0;
    while(q->next != NULL)
        q = q->next;

    return q->value;
}


int main(int argc, char *argv[]) {
    WINDOW *main_w;
    queue_char* queue = NULL;
    int ncols = 0;
    int nlines = 0;
    int x = 0;
    int y = 0;

    int ch = 0;
    int old_ch = 0;

    //initialize Ncurses
    initscr();
    //get current terminal window max coordinates
    getmaxyx(stdscr, nlines, ncols);
    //print general info
    curs_set(0);
    noecho();
    wprintw(stdscr, "Current terminal size: y = %d\tx = %d\n", nlines, ncols);
    wprintw(stdscr, "Use arrows to move in the screen\nUse CTRL+Z to undo or CTRL+SHIFT+Z for redo\nUse CTRL+S to prompt save\nUse CTRL+Q to quit\n\n");
    attron(A_BOLD);
    wprintw(stdscr, "Press any button to continue ");
    attroff(A_BOLD);
    getch();
    wclear(stdscr);
    curs_set(1);
    //create the main window
    main_w = newwin(nlines, ncols, y, x);
    raw();
    keypad(main_w, 1);
    noecho();

    while(1) {
        ch = wgetch(main_w);
        if(ch == KEY_EXIT) { //'q'
            wclear(main_w);
            wmove(main_w, 0, 0);
            //free Ncurses window
            delwin(main_w);
            //ask confirm
            break;
        }
        //INSERT HERE RESIZE
        getmaxyx(stdscr, nlines, ncols);
        wmove(main_w, 0, 0);
        switch(ch) {
            case KEY_UP:
                if(y-1 >= 0)
                    y--;
                //wprintw(main_w, "\nUp Arrow");
                break;
            case KEY_DOWN:
                if(y+1 < nlines)
                    y++;
                //wprintw(main_w, "\nDown Arrow");
                break;
            case KEY_LEFT:
                if(x-1 >= 0)
                    x--;
                //wprintw(main_w, "\nLeft Arrow");
                break;
            case KEY_RIGHT:
                if(x+1 < ncols)
                    x++;
                //wprintw(main_w, "\nRight Arrow");
                break;
            case KEY_RESIZE:
                mvwprintw(main_w, "\nResize event")
                getmaxyx(main_w, nlines, ncols);
                if(y >= nlines)
                    y = nlines-1;
                if(x >= ncols)
                    y = ncols-1;
                break;
            //TODO add undo e redo buttons (with push and pop)
            default:
                attron(A_BOLD);
                mvwprintw(main_w, y, x, "%c", ch);
                attroff(A_BOLD);
                break;
        }
        wmove(main_w, y, x);
        //update window content
        wrefresh(main_w);
    }

    //stop Ncurses
    endwin();

    return 0;
}

