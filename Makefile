# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymehdi <ymehdi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/28 19:56:23 by ymehdi            #+#    #+#              #
#    Updated: 2021/10/07 15:25:04 by ymehdi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo

SRCS 	=	srcs/philo.c \
			srcs/utils1.c \
			srcs/routine.c \
			srcs/utils2.c \
			srcs/ft_init.c

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
   ifeq ($(UNAME_S),Linux)
        CC=clang-9
    endif
    ifeq ($(UNAME_S),Darwin)
        CC=clang
    endif

CFLAGS = -Wall -Wextra -Werror

GFLAG = -g3 -fsanitize=address

INCLUDES= -I includes/

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS) $(INCLUDES)

debug :
	$(CC) $(CFLAGS) $(GFLAG) -o $(NAME) $(SRCS)

clean :
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
