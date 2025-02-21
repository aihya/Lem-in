# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aihya <aihya@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/30 10:17:50 by aihya             #+#    #+#              #
#    Updated: 2020/01/16 15:59:17 by aihya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = lem-in

SRC_NAME =	main.c \
			hash_table.c \
			parser.c \
			links.c

OBJ_NAME =	$(SRC_NAME:.c=.o)

SRC_PATH =	src
OBJ_PATH =	obj

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

CFLAGS = -Wall \
		 -Werror \
		 -Wextra

INCLUDE =	-Iinclude \
			-Ilibft/include

LIBS = -Llibft -lft

DEPS = include/lem-in.h

all : $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@echo "\033[1;34mCreating $(NAME)\033[0m"
	@gcc $(OBJ) $(LIBS) -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(DEPS)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo "Compiling \033[1;36m[$<]\033[0m to \033[1;32m[$@]\033[0m"
	@gcc $(CFLAGS) -g $(INCLUDE) -o $@ -c $<

clean :
	@make -C libft clean
	@echo "\033[1;33mRemoving $(NAME)'s objects directory\033[0m"
	@/bin/rm -rf $(OBJ_PATH) 2> /dev/null

fclean : clean
	@make -C libft fclean
	@echo "\033[1;33mRemoving $(NAME)\033[0m"
	@/bin/rm -f $(NAME)

re : fclean all
