#include "../include/hello.h"

#define ENTER 10
#define ESCAPE 27

void ft_init_curses(void)
{
	//	g_mut = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&g_mut);
	initscr();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_WHITE,COLOR_RED);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
	bkgd(COLOR_PAIR(1));
	move(0, 0);
	printw("A problem has been detected and windows been shut down to prevent damage to your computer.");
	move(1, 0);
	printw("UNMOUNTABLE_BOOT_VOLUME :");
	move(2, 0);
	printw("*** STOP: 0X89F1080ED (0X345A3BC5, 0X62348EB3A, 0X0967EAC4F0)");
	refresh();
	pthread_mutex_unlock(&g_mut);
}

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	pthread_mutex_lock(&g_mut);
	wmove(capsule, x, y);
	wclrtoeol(capsule);
	wprintw(capsule, data);
	wrefresh(capsule);
	pthread_mutex_unlock(&g_mut);
}
