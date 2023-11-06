# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/27 12:53:01 by lsohler           #+#    #+#              #
#    Updated: 2023/11/06 14:53:59 by itovar-n         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		= libft.a

SRCS		= \
			array/array_add_str.c\
			array/free_array.c\
			array/ft_arrdup.c\
			array/ft_arrlen.c\
			array/ft_arrsort.c\
			\
			char/ft_isalnum.c\
			char/ft_isalpha.c\
			char/ft_isascii.c\
			char/ft_isdigit.c\
			char/ft_isprint.c\
			char/ft_tolower.c\
			char/ft_toupper.c\
			\
			list/ft_lstadd_back_bonus.c\
			list/ft_lstadd_front_bonus.c\
			list/ft_lstclear_bonus.c\
			list/ft_lstdelone_bonus.c\
			list/ft_lstiter_bonus.c\
			list/ft_lstlast_bonus.c\
			list/ft_lstmap_bonus.c\
			list/ft_lstnew_bonus.c\
			list/ft_lstsize_bonus.c\
			\
			math/ft_abs.c\
			math/ft_mod.c\
			math/ft_dot.c\
			math/ft_vector_lenght.c\
			math/ft_normalize.c\
			math/ft_v_add.c\
			math/ft_v_mul.c\
			math/ft_v_sub.c\
			math/ft_v_scale.c\
			math/ft_deg_to_rag.c\
			math/ft_v_cprod.c\
			math/ft_range.c\
			\
			mem/ft_bzero.c\
			mem/ft_calloc.c\
			mem/ft_memchr.c\
			mem/ft_memcmp.c\
			mem/ft_memcpy.c\
			mem/ft_memmove.c\
			mem/ft_memset.c\
			mem/ft_realloc.c\
			\
			print/ft_putchar_fd.c\
			print/ft_putstr_fd.c\
			print/ft_putnbr_fd.c\
			print/ft_putendl_fd.c\
			\
			quat/euler_to_quat.c\
			quat/quat_conjugate.c\
			quat/quat_create.c\
			quat/quat_multiply.c\
			quat/quat_normalize.c\
			quat/o_vector_to_quat.c\
			quat/quat_add_offset.c\
			quat/quat_sub_offset.c\
			quat/quat_v_create.c\
			quat/v_quat_create.c\
			quat/quat_v_transform.c\
			quat/quat_rotate.c\
			quat/quat_copy.c\
			quat/quat_two_vector_rotation.c\
			\
			str/ft_atof.c\
			str/ft_atoi.c\
			str/ft_itoa.c\
			str/ft_split.c\
			str/ft_strchr.c\
			str/ft_strdup.c\
			str/ft_striteri.c\
			str/ft_strjoin.c\
			str/ft_strjoin_nf.c\
			str/ft_strlcat.c\
			str/ft_strlcpy.c\
			str/ft_strlen.c\
			str/ft_strmapi.c\
			str/ft_strncmp.c\
			str/ft_strcmp.c\
			str/ft_strndup.c\
			str/ft_strnstr.c\
			str/ft_strrchr.c\
			str/ft_strtrim.c\
			str/ft_substr.c\

OBJS	= $(SRCS:.c=.o)


CC		= gcc

CFLAGS	= -Wall -Wextra -Werror -I.

RM		= rm -f

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all: 		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

clean:		
			$(RM) $(OBJS) $(BONUS_OBJS)

fclean:		clean
			$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY: all clean fclean re

