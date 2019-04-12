/*
 * Basso Nicola
 * 4^AI
 */

#include <stdio.h>
#include <ncurses.h>

void test_input(void);
void test_xy(int y, int x);

int main() {
    int y = 0;
    int x = 0;

    x = 3;
    y = 7;

    //inizializza la modalita' curses
    initscr();
    //gestisce i caratteri terminatori cosi' come sono
    cbreak();
    //se l'utente usa la tastiera non stampa i caratteri scritti
    noecho();
    //accetta i tasti FN
    keypad(stdscr, TRUE);

    //stampa nella finestra di curses
    printw("Hello World!\n");

    //test di input controllato
    test_input();

    //aggiorna la finestra con il frame contenente i printw
    refresh();

    //altezza, larghezza
    test_xy(y, x);
    refresh();
    test_xy(x, y);
    //sposta il cursore nelle posizione y x passate

    //attende l'input dell'utente per uscire dalla finestra
    printw("\nPress any key to continue...\n");
    move(y+2, x+2);
    getch();

    //termina curses e tutte le sue finestre
    endwin();

    return 0;
}



void test_input(void) {
    char ch = 0;

    printw("Inserisci un carattere:\n");
    //senza raw() richiederebbe un invio
    ch = getch();

    //accetta anche FN grazie a keypad()
    if(ch == KEY_F(1))
        printw("F1 premuto\n");
    //senza noecho() stamperebbe caratteri sporchi
    else {
        printw("Hai premuto:\n");
        //attiva un attributo dei caratteri (costanti)
        attron(A_BOLD);
        printw("%c\n", ch);
        //disattiva un attributo dei caratteri (costanti)
        attroff(A_BOLD);
    }
}

void test_xy(int y, int x) {
    mvprintw(y, x, "Hi!");
}
