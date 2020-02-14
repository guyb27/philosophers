#include "../include/hello.h"

void		ft_actualize(WINDOW *capsule, char *data, int x, int y)
{
	if (g_gmode == ALL_WINDOWS)
	{
		wmove(capsule, x, y);
		wclrtoeol(capsule);
		wprintw(capsule, data);
		wrefresh(capsule);
	}
}
