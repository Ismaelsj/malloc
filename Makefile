# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 16:07:44 by IsMac             #+#    #+#              #
#    Updated: 2020/10/14 17:15:04 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fPIC

SRCS_PATH = srcs/

INCLUDES_PATH = includes/

SRCS_NAME = block.c \
			area.c \
			malloc.c \
			realloc.c \
			calloc.c \
			free.c \
			merge_block.c \
			size.c \
			search.c \
			show_alloc_mem.c \
			crc32.c \
			print_values.c \
			init_objects.c \
			utils.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = objs/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir $(NAME)

$(NAME): $(OBJS)
	@echo " - Making $(NAME)"
	$(CC) -shared $(CFLAGS) -o $(NAME) $^ $(LIBRARY)
	ln -sf $(NAME) libft_malloc.so

odir:
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c
	@echo " - Compiling $<"
	$(CC) $(CFLAGS) -I $(INCLUDES_PATH) -o $@ -c $<

clean:
	@echo " - Cleaning objs"
	@rm -f $(OBJS)

fclean: clean
	@echo " - Cleaning executable"
	@rm -f $(NAME)
	@rm -rf $(OBJS_PATH)
	@rm -f libft_malloc.so

re: fclean all

.PHONY: clean fclean re odir