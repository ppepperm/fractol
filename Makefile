# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+         #n
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/17 12:14:41 by ppepperm          #+#    #+#              #
#    Updated: 2019/11/17 12:14:43 by ppepperm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= fractol
SRC := speed_by_billy_idol.c mandelbrot.c mandel_speed.c ship.c ship_speed.c spider1.c spider1_speed.c julia.c complex.c free.c main.c
OBJ := $(patsubst %.c, %.o, $(SRC))
CFLAGS := -Wall -Wextra -Werror
LIB_FLAG := -L libft/ -lft  -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -framework OpenCl
LINUX_FLAG := -L libft/ -lft -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11  -l OpenCL -lm
INCLUDES := /includes

all: $(NAME)

%.o : src/%.c $(INCLUDES)
		@gcc -c $(CFLAGS) -I $(INCLUDES) $< -o $@
		@echo $(patsubst src/%.c, %, $<)

$(NAME): $(OBJ)
		@make -C libft
		@make -C minilibx_macos
		@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LIB_FLAG)
		@echo "DONE"

LINUX : $(OBJ)
		@make -C libft
		@gcc -o $(NAME) $(CFLAGS) $(OBJ) $(LINUX_FLAG)
		@echo "DONE"

clean:
		@rm -f $(OBJ)
		@make -C libft clean

fclean: clean
		@rm -f $(NAME)
		@make -C libft fclean

re: fclean $(NAME)

.PHONY: all clean fclean re

