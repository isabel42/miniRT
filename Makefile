# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 17:19:38 by lsohler           #+#    #+#              #
#    Updated: 2023/11/01 13:21:09 by itovar-n         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = \
		srcs/main.c\
		\
		srcs/draw/render.c\
		\
		srcs/free/free.c\
		srcs/free/error.c\
		\
		srcs/key/key.c\
		\
		srcs/interpolation/cylinder_param.c\
		srcs/interpolation/cn_param.c\
		srcs/interpolation/cylinder.c\
		srcs/interpolation/plan.c\
		srcs/interpolation/sphere.c\
		srcs/interpolation/cone.c\
		\
		srcs/parsing/objects.c\
		srcs/parsing/utils.c\
		srcs/parsing/rgb.c\
		srcs/parsing/scenario.c\
		srcs/parsing/parsing.c\
		\
		srcs/tracing/hit.c\
		srcs/tracing/shadow_ray.c\
		srcs/tracing/tracing.c\
		\
		gnl/get_next_line.c\
		gnl/get_next_line_utils.c\
		\
		
OBJS 	= ${SRCS:.c=.o}

NAME 	= miniRT

FT_NAME = ./libft/libft.a

MLX_NAME = ./minilibx/libmlx.a

CC		= gcc

RM		= rm -f

CFLAGS	= -Wextra -Wall -Werror

SANITIZE = -fsanitize=address -g3

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