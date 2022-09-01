# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mouarsas <mouarsas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/23 21:33:00 by mouarsas          #+#    #+#              #
#    Updated: 2022/08/30 21:19:19 by mouarsas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

cc = gcc

FLAGS = -Wall -Wextra -Werror

SRC =	die.c\
		eating.c\
		ft_utils.c\
		main.c\
		philosophers.c\
		threads.c\


OBJ = $(SRC:%.c=%.o)


all: $(NAME)

$(NAME) : $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c
	$(CC) -c $< -o $@ $(FLAGS)

clean :
	rm -fr *.o

fclean : clean
	rm -fr $(NAME)

re : fclean all
