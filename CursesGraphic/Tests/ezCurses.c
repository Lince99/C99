#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	initscr();
	noecho();
	curs_set(FALSE);
	mvprintw(0, 0, "Hello, world!");
	mvprintw(10, 10, "Hi!");
 	refresh();

	sleep(2);

	endwin(); // Restore normal terminal behavior
	return 0;
}
