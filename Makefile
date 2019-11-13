# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: IsMac <IsMac@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 16:07:44 by IsMac             #+#    #+#              #
#    Updated: 2019/11/13 21:50:34 by IsMac            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HOSTTYPE ?= $(shell uname -m)_$(shell uname -s)

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

TEST = test

CFLAGS = -Wall -Wextra -Werror

SRCS_PATH = srcs/

INCLUDES_PATH = includes/

SRCS_NAME = block.c \
			area.c \
			malloc.c \
			init_global.c \
			size.c \

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))

OBJS_PATH = objs/

OBJS_NAME = $(SRCS_NAME:.c=.o)

OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

all: odir $(NAME)

$(NAME): $(OBJS)
	@echo " - Making $(NAME)"
	$(CC) -shared $(CFLAGS) -o $(NAME) $^ $(LIBRARY)
	# ln -sf $(NAME) libft_malloc.so

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
	@rm -f $(TEST)
	@rm -f libft_malloc.so

test:
	@echo " - Compiling $(TEST)"
	$(CC) $(TEST).c -o $(TEST) $(NAME) -I $(INCLUDES_PATH)

re: fclean all

.PHONY: clean fclean re odir