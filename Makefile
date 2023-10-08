# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 17:19:38 by lsohler           #+#    #+#              #
#    Updated: 2023/10/08 17:05:51 by itovar-n         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = \
		srcs/main.c\
		\
		srcs/draw/bresenham.c\
		\
		srcs/free/free.c\
		srcs/free/error.c\
		\
		srcs/parsing/objects.c\
		srcs/parsing/utils.c\
		srcs/parsing/rgb.c\
		srcs/parsing/scenario.c\
		srcs/parsing/parsing.c\
		srcs/parsing/meta.c\
		\
		srcs/test/print.c\
		srcs/test/cameratest.c\
		srcs/test/mouse.c\
		srcs/test/key.c\
		srcs/test/raytest.c\
		srcs/test/scenariobox.c\
		srcs/test/form.c\
		srcs/tracing/hit.c\
		\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		\
		srcs/in_fig.c\
		
OBJS 	= ${SRCS:.c=.o}

NAME 	= miniRT

FT_NAME = ./libft/libft.a

MLX_NAME = ./minilibx/libmlx.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wextra -Wall -Werror

INCLUDE = -I./includes -I./libft/ -I./minilibx/

.c.o:	
			${CC} ${CFLAGS} $(INCLUDE) -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS} ${FT_NAME} ${MLX_NAME}
			${CC} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} -L./minilibx/ -lmlx -L./libft/ -lft -framework OpenGL -framework AppKit

all:		${NAME}

${FT_NAME}:
	make all -C ./libft/

${MLX_NAME}:
	make -C ./minilibx

clean:
			make clean -C ./libft
			make clean -C ./minilibx	
			${RM} ${OBJS}

fclean: 	clean
			make fclean -C ./libft
			${RM} ${MLX_NAME}
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re