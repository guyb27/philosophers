# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dzonda <dzonda@student.le-101.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/10 20:37:15 by dzonda            #+#    #+#              #
#    Updated: 2020/02/17 22:05:19 by dzonda           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCDIR = src
OBJDIR = obj
INCDIR = include

MAKEFILE_NAME = Makefile-$(lastword $(subst /, ,$(NAME)))
VERBOSE = FALSE
DEBUG = FALSE

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I$(INCDIR)

SRC_FILES =	\
			ft_atoi.c \
			ft_bzero.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isblank.c \
			ft_isdigit.c \
			ft_islower.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_isupper.c \
			ft_itoa.c \
			ft_lstadd.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_nbrlen.c \
			ft_putchar.c \
			ft_putchar_fd.c \
			ft_putendl.c \
			ft_putendl_fd.c \
			ft_putnbr.c \
			ft_putnbr_fd.c \
			ft_putstr.c \
			ft_putstr_fd.c \
			ft_stradel.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strdup_free.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strjoin_free.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_wordcount.c \
			ft_wordlen.c \
			get_next_line.c \
			ft_tabdel.c \
			ft_tabdup.c \
			ft_tablen.c \
			ft_getenv.c \
			ft_strdel_in_tab.c \
			ft_str_isalnum.c \
			ft_malloc_cmd.c \
			ft_putstr_color.c \
			ft_add_str_at.c \
			ft_strreplace.c \
			ft_add_to_str.c \
			ft_str_isblank.c \
			ft_strisdigit.c \
			ft_reverse_tab.c \
			ft_concat_tab_to_str.c \
			ft_addstrtostrat.c \
			ft_insert_char_in_str.c \
			ft_chardel_at.c \
			ft_mini_printf.c \
			ft_isquote.c \
			ft_printf.c \
			pf_handle.c \
			pf_handle_char.c \
			pf_handle_float.c \
			pf_handle_hex.c \
			pf_handle_oct.c \
			pf_handle_p.c \
			pf_handle_percent.c \
			pf_handle_signed_int.c \
			pf_handle_str.c \
			pf_handle_unsigned_int.c \
			pf_bzero.c \
			pf_ftoa.c \
			pf_isdigit.c \
			pf_isinstr.c \
			pf_itoa.c \
			pf_itoa_base.c \
			pf_memalloc.c \
			pf_memdel.c \
			pf_strchr.c \
			pf_strcut.c \
			pf_strdup.c \
			pf_strlen.c \
			pf_strnew.c \
			pf_strnjoin.c \
			pf_strsub.c \
			pf_tabset.c \
			pf_lstaddend.c \
			pf_lstnew.c \
			pf_lstprint.c \
			pf_parse_tests.c \
			pf_parsing.c

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

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(HIDE)echo $(MAKEFILE_NAME): [$(NB_FILES_COMPILED)/$(NB_FILES)] "Linking ->" $@
	$(HIDE)ar rcs $(NAME) $(OBJS)

-include $(DEPS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(NB_FILES_INCREMENT)
	@echo $(MAKEFILE_NAME): [$(NB_FILES_COMPILED)/$(NB_FILES)] "Building ->" $@
	$(HIDE)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MMD
	@tput cuu1
	@tput el

$(OBJDIR):
	$(HIDE)$(MKDIR) $(OBJDIR)

valgrind: $(NAME)
	@echo $(MAKEFILE_NAME): "Executing $(NAME) with debug mode :" $(DEBUG)
	$(HIDE)valgrind --leak-check=full --track-origins=yes ./$(NAME)
	$(HIDE)$(RM) $(NAME).dSYM $(ERRIGNORE)

clean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Clean done !

fclean:
	$(HIDE)$(RM) $(OBJDIR) $(ERRIGNORE)
	$(HIDE)$(RM) $(NAME) $(ERRIGNORE)
	@echo $(MAKEFILE_NAME): Fclean done !

re: fclean all
