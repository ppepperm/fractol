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
SRC := src/speed_by_billy_idol.c src/mandelbrot.c src/mandel_speed.c src/ship.c src/ship_speed.c src/spider1.c src/spider1_speed.c src/julia.c src/complex.c src/free.c src/main.c src/shortcut1.c src/shortcut2.c src/shortcut3.c src/shortcut4.c
OBJ := $(patsubst %.c, %.o, $(SRC))
CFLAGS := -Wall -Wextra -Werror  -I includes
LIB_FLAG :=  -L libft/ -lft  -L minilibx_macos -lmlx -framework OpenGL -framework AppKit -framework OpenCl
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

