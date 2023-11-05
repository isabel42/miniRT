# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsohler <lsohler@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 17:19:38 by lsohler           #+#    #+#              #
#    Updated: 2023/11/05 17:49:37 by lsohler          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = \
		srcs/main.c\
		\
		srcs/draw/render.c\
		srcs/draw/color.c\
		\
		srcs/free/free.c\
		srcs/free/error.c\
		srcs/free/hit_collector.c\
		\
		srcs/key/key.c\
		\
		srcs/interpolation/cylinder_param.c\
		srcs/interpolation/cylinder.c\
		srcs/interpolation/plan.c\
		srcs/interpolation/sphere.c\
		srcs/interpolation/cone.c\
		srcs/interpolation/cn_param.c\
		\
		srcs/parsing/objects.c\
		srcs/parsing/utils.c\
		srcs/parsing/rgb.c\
		srcs/parsing/scenario.c\
		srcs/parsing/parsing.c\
		\
		srcs/texture/texture.c\
		srcs/texture/sphere_texture.c\
		srcs/texture/plan_texture.c\
		srcs/texture/init.c\
		srcs/texture/rgb.c\
		\
		srcs/tracing/hit.c\
		srcs/tracing/shadow_ray.c\
		srcs/tracing/tracing.c\
		\
		srcs/view/camera.c\
		srcs/view/init.c\
		srcs/view/utils.c\
		srcs/view/key_press_view.c\
		srcs/view/mouse.c\
		srcs/view/form.c\
		srcs/view/bresenham.c\
		srcs/view/rotation.c\
		srcs/view/draw.c\
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

# SANITIZE = -fsanitize=address -g3

INCLUDE = -I./includes -I./libft/ -I./minilibx/

.c.o:	
			${CC} ${SANITIZE} ${CFLAGS} $(INCLUDE) -c $< -o ${<:.c=.o}

${NAME}: 	${OBJS} ${FT_NAME} ${MLX_NAME}
			${CC} ${SANITIZE} ${CFLAGS} ${INCLUDE} ${OBJS} -o ${NAME} -L./minilibx/ -lmlx -L./libft/ -lft -framework OpenGL -framework AppKit

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