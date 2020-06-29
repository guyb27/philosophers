# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzonda <dzonda@student.le-101.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/24 18:33:54 by dzonda            #+#    #+#              #
#    Updated: 2020/02/17 22:06:14 by dzonda           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBDIR = libft

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))
VERBOSE = FALSE
DEBUG = FALSE

CC = gcc
INC = -I$(INCDIR) #-Isfml/CSFML/include
CFLAGS =  	-Wall -Wextra -Werror -Wunused -Wunreachable-code \
			-Wno-deprecated-declarations -std=c11 -fms-extensions -g3
CSFML = -fms-extensions -lcsfml-graphics -lcsfml-window -lcsfml-system
LDFLAGS = -Llibft $(CSFML)
LDLIBS = -lft -lncurses -lpthread -D_REENTRANT

SRC_FILES = \
			utils.c \
			main.c \
			ft_main_thread.c \
			management_error.c \
			handle_define.c \
			menu.c \
			wand_locate.c \
			handle_main_menu.c \
			init.c \
			free.c \
			eat.c \
			think.c \
			rest.c \
			create.c \
			philo.c \
			get_philo_locate.c \
			manage_wand.c \
			visu.c

SRCS = $(foreach file, $(SRC_FILES), $(addprefix $(SRCDIR)/, $(file)))
OBJS = $(subst $(SRCDIR),$(OBJDIR),$(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

HIDE = @
MAKE = make -C
RM = rm -rf
MKDIR = mkdir -p
ERRIGNORE = 2>/dev/null

ifeq ($(VERBOSE),TRUE)
	HIDE =
endif
ifeq ($(DEBUG),TRUE)
	CFLAGS += -g3 -ggdb3
endif

NB_FILES = $(words $(SRC_FILES))
NB_FILES_COMPILED = 0
NB_FILES_INCREMENT = @$(eval NB_FILES_COMPILED=$(shell echo $$(($(NB_FILES_COMPILED) + 1))))
SHELL = /bin/bash

.PHONY: all clean fclean re lib

all: lib $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	@echo $(MAKEFILE_NAME): [$(NB_FILES_COMPILED)/$(NB_FILES)] "Linking ->" $@
	$(HIDE)$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) $(INC) -o $(NAME)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c #inc_path?
	@$(NB_FILES_INCREMENT)
	@echo $(MAKEFILE_NAME): [$(NB_FILES_COMPILED)/$(NB_FILES)] "Building ->" $@
	$(HIDE)$(CC) $(CFLAGS) $(INC) -c $< -o $@ -MMD
	@tput cuu1
	@tput el

$(OBJDIR):
	$(HIDE)$(MKDIR) $(OBJDIR)

lib:
	$(HIDE)$(MAKE) $(LIBDIR)

valgrind: lib $(NAME)
	@echo $(MAKEFILE_NAME): "Executing $(NAME) with debug mode :" $(DEBUG)
	$(HIDE)valgrind --leak-check=full --track-origins=yes ./$(NAME)
	$(HIDE)$(RM) $(NAME).dSYM $(ERRIGNORE)

clean:
	$(HIDE)$(MAKE) $(LIBDIR) clean
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Clean done !

fclean:
	$(HIDE)$(MAKE) $(LIBDIR) fclean
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all
