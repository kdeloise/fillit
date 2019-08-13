# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/18 16:30:59 by vtouffet          #+#    #+#              #
#    Updated: 2019/07/23 10:20:04 by tgrandpa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC	=	validation.c \
		read.c \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): 
	gcc -c $(NAME).c $(SRC)
	gcc -o $(NAME) $(NAME).o $(OBJ) -L. libft/libft.a
	
clean:
	/bin/rm -rf $(NAME).o $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean all
