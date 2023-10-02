SRCS = \
		srcs/main.c\
		\
		srcs/free/free.c\
		\
		srcs/parsing/parsing_diam.c\
		srcs/parsing/parsing_obj.c\
		srcs/parsing/parsing_pos.c\
		srcs/parsing/parsing_rgb.c\
		srcs/parsing/parsing.c\
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