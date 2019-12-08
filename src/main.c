#include "hello.h"
	static void *
thread_start(void *arg)
{
	struct thread_info *tinfo = arg;
	char *uargv, *p;

	printf("Thread %d: top of stack near %p; argv_string=%s\n",
			tinfo->thread_num, &p, tinfo->argv_string);

	uargv = strdup(tinfo->argv_string);
	if (uargv == NULL)
		handle_error("strdup");

	for (p = uargv; *p != '\0'; p++)
		*p = toupper(*p);

	return uargv;
}

	int
main(int argc, char *argv[])
{
	int s, tnum, opt, num_threads;
	struct thread_info *tinfo;
	pthread_attr_t attr;
	int stack_size;
	void *res;

	//The window we'll be rendering to
	SDL_Window* sdl_window = NULL;
	//The surface contained by the window
	SDL_Surface* sdl_screenSurface = NULL;
	//The image we will load and show on the screen
	SDL_Surface* sdl_hello_world = NULL;
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	//Initialize SDL
	if (init_sdl(&sdl_window, &sdl_screenSurface))
	{
		//Create window
		loadMedia(&sdl_hello_world);
		SDL_BlitSurface( sdl_hello_world, NULL, sdl_screenSurface, NULL );
		SDL_UpdateWindowSurface( sdl_window );
		pause();
		close_sdl(&sdl_window, &sdl_hello_world);
	}

	/* The "-s" option specifies a stack size for our threads */

	stack_size = -1;
	while ((opt = getopt(argc, argv, "s:")) != -1) {
		switch (opt) {
			case 's':
				stack_size = strtoul(optarg, NULL, 0);
				break;

			default:
				fprintf(stderr, "Usage: %s [-s stack-size] arg...\n",
						argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	num_threads = argc - optind;

	/* Initialize thread creation attributes */

	s = pthread_attr_init(&attr);
	if (s != 0)
		handle_error_en(s, "pthread_attr_init");

	if (stack_size > 0) {
		s = pthread_attr_setstacksize(&attr, stack_size);
		if (s != 0)
			handle_error_en(s, "pthread_attr_setstacksize");
	}

	/* Allocate memory for pthread_create() arguments */

	tinfo = calloc(num_threads, sizeof(struct thread_info));
	if (tinfo == NULL)
		handle_error("calloc");

	/* Create one thread for each command-line argument */

	for (tnum = 0; tnum < num_threads; tnum++) {
		tinfo[tnum].thread_num = tnum + 1;
		tinfo[tnum].argv_string = argv[optind + tnum];

		/* The pthread_create() call stores the thread ID into
		 *                   corresponding element of tinfo[] */

		s = pthread_create(&tinfo[tnum].thread_id, &attr,
				&thread_start, &tinfo[tnum]);
		if (s != 0)
			handle_error_en(s, "pthread_create");
	}

	/* Destroy the thread attributes object, since it is no
	 *               longer needed */

	s = pthread_attr_destroy(&attr);
	if (s != 0)
		handle_error_en(s, "pthread_attr_destroy");

	/* Now join with each thread, and display its returned value */

	for (tnum = 0; tnum < num_threads; tnum++) {
		s = pthread_join(tinfo[tnum].thread_id, &res);
		if (s != 0)
			handle_error_en(s, "pthread_join");

		printf("Joined with thread %d; returned value was %s\n",
				tinfo[tnum].thread_num, (char *) res);
		free(res);      /* Free memory allocated by thread */
	}

	free(tinfo);
	exit(EXIT_SUCCESS);
}
