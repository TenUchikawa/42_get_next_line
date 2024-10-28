# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tuchikaw <tuchikaw@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 02:34:43 by tuchikaw          #+#    #+#              #
#    Updated: 2024/10/29 02:35:28 by tuchikaw         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS			=	get_next_line.c \
					get_next_line_utils.c


NAME = get_next_line.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

OBJS			= $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re