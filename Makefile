# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 16:26:07 by dpinto            #+#    #+#              #
#    Updated: 2025/06/02 03:21:53 by dpinto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_FLAGS = -Lmlx -lmlx -L/usr/lib -lXext -lX11 -lm

SRCS = srcs/main.c \
       srcs/parse.c \
       srcs/parse_fields.c \
       srcs/parse_map.c \
       srcs/map_check.c \
       srcs/map_utils.c \
       srcs/validate.c \
       srcs/validate_walls.c \
       srcs/helper.c \
       srcs/helper_free.c \
       srcs/file_utils.c \
       srcs/print_fields.c \
       srcs/window.c \
       srcs/window_init.c \
       srcs/window_texture.c \
       srcs/parse_fields_utils2.c \
       srcs/raycasting.c \
       srcs/raycasting_calc.c \
       srcs/raycasting_texture.c \
       srcs/raycasting_draw.c \
       srcs/raycasting_utils.c \
       srcs/movement.c \
       srcs/movement_utils.c \
       srcs/movement_utils2.c

OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a
MLX = mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

%.o: %.c includes/cube3d.h
	$(CC) $(CFLAGS) -I includes -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
