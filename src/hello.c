#include "../include/hello.h"

#define ENTER 10
#define ESCAPE 27

void ft_init_curses(void)
{
	initscr();
	start_color();
	init_pair(1,COLOR_WHITE,COLOR_BLUE);
	init_pair(2,COLOR_BLUE,COLOR_WHITE);
	init_pair(3,COLOR_RED,COLOR_WHITE);
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
	bkgd(COLOR_PAIR(1));
}

int ft_init_philos(void)
{
	int key;
	ft_init_curses();
	move(3,50);
	printw("Life Point: [          ]");
	move(4,50);
	printw("NAME: Philo1");
	move(5,50);
	printw("STATE: NOTHING");
	move(6,50);
	printw("Time State: [          ]");
	move(10,10);
	printw("Life Point: [          ]");
	move(11,10);
	printw("NAME: Philo2");
	move(12,10);
	printw("STATE: NOTHING");
	move(13,10);
	printw("Time State: [          ]");
	move(10,90);
	printw("Life Point: [          ]");
	move(11,90);
	printw("NAME: Philo3");
	move(12,90);
	printw("STATE: NOTHING");
	move(13,90);
	printw("Time State: [          ]");
	move(17,10);
	printw("Life Point: [          ]");
	move(18,10);
	printw("NAME: Philo4");
	move(19,10);
	printw("STATE: NOTHING");
	move(20,10);
	printw("Time State: [          ]");
	move(17,90);
	printw("Life Point: [          ]");
	move(18,90);
	printw("NAME: Philo5");
	move(19,90);
	printw("STATE: NOTHING");
	move(20,90);
	printw("Time State: [          ]");
	move(24,30);
	printw("Life Point: [          ]");
	move(25,30);
	printw("NAME: Philo6");
	move(26,30);
	printw("STATE: NOTHING");
	move(27,30);
	printw("Time State: [          ]");
	move(24,70);
	printw("Life Point: [          ]");
	move(25,70);
	printw("NAME: Philo7");
	move(26,70);
	printw("STATE: NOTHING");
	move(27,70);
	printw("Time State: [          ]");
	refresh();
	//delwin(messagebar);
	//while(1);
	do
	{
		//int selected_item;
		//WINDOW **menu_items;
		key=getch();
		//werase(messagebar);
		//wrefresh(messagebar);
		if (key==KEY_F(1))
		{
		/*	menu_items=draw_menu(0);
			selected_item=scroll_menu(menu_items,8,0);
			delete_menu(menu_items,9);
			if (selected_item<0)
				wprintw(messagebar,"Vous n’avez pas selectionne de rubrique.");
			else
				wprintw(messagebar, "Vous avez selectionne la rubrique %d.",selected_item+1);
			touchwin(stdscr);
		*/
			move(5,57);
			clrtoeol();
			printw("MANGE");
			refresh();
		}
		else if (key==KEY_F(2))
		{
		/*
			menu_items=draw_menu(20);
			selected_item=scroll_menu(menu_items,8,20);
			delete_menu(menu_items,9);
			if (selected_item<0)
				wprintw(messagebar,"Vous n’avez pas selectionne de rubrique.");
			else
				wprintw(messagebar, "Vous avez selectionne la rubrique %d.", selected_item+1);
			touchwin(stdscr);
			refresh();
		*/
			move(5,57);
			clrtoeol();
			printw("Se repose");
			refresh();
		}
	} while (key!=ESCAPE);
	endwin();
	return 0;
}
