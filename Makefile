# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: domi <domi@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/31 10:43:27 by dmaessen          #+#    #+#              #
#    Updated: 2024/02/19 20:29:05 by domi             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast -g #-fsanitize=leak #-O1

LIBFT = libft/libft.a

HEADERS = -I ./include -I MLX42/include -I libft/

LIB = MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm $(LIBFT)

SRC =  src/main.c \
	src/parsing/parse_input.c src/parsing/parse_file.c src/parsing/parse_map.c \
	src/parsing/parse_spaces.c src/parsing/parse_checks.c \
	src/utils/error_msg.c src/utils/free.c src/utils/parsing_utils.c src/utils/free_text.c \
	src/raycasting/start_loop.c src/raycasting/move.c src/raycasting/init.c src/raycasting/draw.c \
	src/raycasting/background.c src/raycasting/move_keys.c \


OBJ = ${SRC:.c=.o}
OBJ_DIR := obj/
OBJECTS_PREFIXED := $(addprefix $(OBJ_DIR), $(OBJ))

all: libmlx42 libft_build $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

libmlx42:
	@git submodule update --init
	@if [ ! -f MLX42/build/libmlx42.a ]; then \
		cmake MLX42 -B MLX42/build && make -C MLX42/build -j4; \
	fi
#	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

libft_build:
	@$(MAKE) -C libft/

$(NAME): $(OBJECTS_PREFIXED) libmlx42
	@$(CC) $(OBJECTS_PREFIXED) $(LIB) $(HEADERS) -o $(NAME)
	@echo "cub3d is ready!"

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C libft/
	@make clean -C MLX42/build/

fclean: clean
	@rm -f $(LIBFT)
	@rm -f MLX42/build/libmlx42.a
	@rm -f $(NAME)

re: fclean
	@$(MAKE) all

.PHONY:	all, clean, fclean, re, libmlx42, libft_build
