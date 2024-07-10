# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arlarzil <armand.larzilliere@gmail.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 20:28:41 by arlarzil          #+#    #+#              #
#    Updated: 2024/07/10 20:04:22 by arlarzil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NORMAL_DIR		=	src/

SRC_NORMAL		=	main			\
					init			\
					destruct		\
					run				\
					routine			\
					quick_mutex		\
					get_timestamp	\
					eat				\
					ft_atoi			\

SRC_TO_FILENAME_NORMAL		= $(addsuffix .c, $(addprefix $(SRC_NORMAL_DIR), $(SRC_NORMAL)))

OBJ_NORMAL		=	$(SRC_TO_FILENAME_NORMAL:.c=.o)

OBJS_NORMAL		=	$(OBJ_COMMON) $(OBJ_NORMAL)

NAME 			= 	philo

BONUS_NAME		= 	philo

CC 				= cc

CFLAGS 	= -Wall -Wextra -Werror -Icommon -g3 -pthread

all: 	$(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

$(NAME): $(OBJS_NORMAL)
	$(CC) -o $(NAME) $(OBJS_NORMAL) $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

auteur:
	echo $(USER) > auteur

.PHONY: fclean all re clean
