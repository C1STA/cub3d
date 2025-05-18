# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 16:26:07 by dpinto            #+#    #+#              #
#    Updated: 2025/05/18 06:15:21 by dpinto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cube3D
CC		= cc
#CFLAGS	= -Wall -Wextra -Werror

LIBFT_DIR	= libft
MLX_DIR		= mlx
INCLUDE_DIR	= includes

SRCS_DIR	= srcs
SRCS		= $(addprefix $(SRCS_DIR)/, main.c parse.c helper.c print_fields.c)
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(MLX_DIR)/libmlx.a:
	@make -s -C $(MLX_DIR)

$(LIBFT_DIR)/libft.a:
	@make -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -lmlx -Llibft -lft -lXext -lX11 -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -o $@

clean:
	@make -s -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@make -s -C $(MLX_DIR) clean

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re MLX LIBFT