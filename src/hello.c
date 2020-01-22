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

int ft_init_philos(void)
{
	//int key;
	ft_init_curses();
	move(3,50);
	printw("NAME: Philo1");
	move(4,50);
	printw("Life Point: [          ]");
	move(5,50);
	printw("STATE: NOTHING");
	move(6,50);
	printw("Time State: [          ]");
	move(10,10);
	printw("NAME: Philo2");
	move(11,10);
	printw("Life Point: [          ]");
	move(12,10);
	printw("STATE: NOTHING");
	move(13,10);
	printw("Time State: [          ]");
	move(10,90);
	printw("NAME: Philo3");
	move(11,90);
	printw("Life Point: [          ]");
	move(12,90);
	printw("STATE: NOTHING");
	move(13,90);
	printw("Time State: [          ]");
	move(17,10);
	printw("NAME: Philo4");
	move(18,10);
	printw("Life Point: [          ]");
	move(19,10);
	printw("STATE: NOTHING");
	move(20,10);
	printw("Time State: [          ]");
	move(17,90);
	printw("NAME: Philo5");
	move(18,90);
	printw("Life Point: [          ]");
	move(19,90);
	printw("STATE: NOTHING");
	move(20,90);
	printw("Time State: [          ]");
	move(24,30);
	printw("NAME: Philo6");
	move(25,30);
	printw("Life Point: [          ]");
	move(26,30);
	printw("STATE: NOTHING");
	move(27,30);
	printw("Time State: [          ]");
	move(24,70);
	printw("NAME: Philo7");
	move(25,70);
	printw("Life Point: [          ]");
	move(26,70);
	printw("STATE: NOTHING");
	move(27,70);
	printw("Time State: [          ]");
	refresh();
	/*	do
		{
		key=getch();
		if (key==KEY_F(1))
		{
		move(5,57);
		clrtoeol();
		printw("MANGE");
		refresh();
		}
		else if (key==KEY_F(2))
		{
		move(5,57);
		clrtoeol();
		printw("Se repose");
		refresh();
		}
		} while (key!=ESCAPE);*/
	//	endwin();
	return 0;
}
