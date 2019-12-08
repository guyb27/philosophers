# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: dzonda <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/24 18:33:54 by dzonda       #+#   ##    ##    #+#        #
#    Updated: 2019/12/08 19:35:35 by gmadec      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

.PHONY: all re clean fclean lib

NAME = philo

MAKE = make
CC = gcc
CFLAGS = #-Wall -Werror -Wextra -Wunused -Wunreachable-code
CPPFLAGS = -I ./include/
LDLIBS = -lft
LDFLAGS = -Llibft/
RM = rm -f

SRCS_PATH = ./src/
OBJS_PATH = ./obj/
INCS_PATH = ./include/
LIB_PATH = ./libft/

SRCS_NAME =	\
			hello.c \
			main.c

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_PATH),$(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH),$(OBJS_NAME))

NB_FILES = $(words $(SRCS_NAME))
SHELL = /bin/bash # just because sh print -n from echo
COLS = $(shell tput cols)
DEL_DSYMFILE = $(shell [ -e a.out.dSYM ] && echo rm -rf a.out.dSYM)

all: $(NAME)

$(NAME): init lib $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS) $(LDLIBS) -Fframeworks -framework SDL2 -rpath frameworks
	@printf "\e[?25h"	# set cursor to visible
	@tput setaf 10 	# set green color
	@tput bold
	@$(eval CURSOR := $(if $(CURSOR),$(CURSOR),0)) # is CURSOR var set ?
	@echo -n "[ $(NAME)    ] Compiled $(CURSOR)/$(NB_FILES) files."
	@tput sgr0 	# reset color
	@tput el 	# clear from cursor to end of line
	@echo ""
	@tput el 	# clear from cursor to end of line

init:
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@tput cuu 4

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@$(eval CURSOR=$(shell echo $$(($(CURSOR) + 1))))
	@$(eval PERCENT=$(shell printf "[%3d/%3d - \e[1m\e[93m%3d%%\e[0m]" $(CURSOR) $(NB_FILES) $$(($(CURSOR) * 100 / $(NB_FILES)))))
	@$(eval LOADSIZE=$(shell echo $$(($(CURSOR) * $(COLS) / $(NB_FILES)))))
	@printf "\e[?25l\e[s\e[35m\e[44m"
	@tput setaf $$((($(CURSOR)%7)+9))
	@number=1 ; while [[ $$i -le $(LOADSIZE)-1 ]] ; do \
        	printf "▌" ; \
        	((i = i + 1)) ; \
    	done
	@printf "\e[0K\e[0m\n\e[1m\e[93m"
	@echo -n "[ $(NAME) ] Compiling: "
	@printf "\e[0m"			# reset color
	@echo -n "$(PERCENT) $@"
	@printf "\e[0K\n\e[u\e[?25h"
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

val: lldb
	valgrind --leak-check=full --track-origins=yes ./a.out

valgrind: lldb
	valgrind --leak-check=full --track-origins=yes ./a.out

valsup: lldb
	valgrind --gen-suppressions=all --leak-check=full --track-origins=yes --show-leak-kinds=all ./a.out

lldb:
	gcc -ggdb3 src/*.c libft/src/*.c -I include -I libft/include

lib:
	@make -C $(LIB_PATH)

clean:
	@$(MAKE) -C $(LIB_PATH) clean
	@$(RM) $(OBJS)
	@rm -rf obj

fclean: clean
	@$(MAKE) -C $(LIB_PATH) fclean
	@$(RM) $(NAME)
	@rm -rf a.out
	@printf "\e[1;31m"	# set red color
	@echo "[ $(NAME)   ] deleted."
	@printf "\e[0m"		# reset color
	@rm -rf obj
	$(DEL_DSYMFILE)

re: fclean all
