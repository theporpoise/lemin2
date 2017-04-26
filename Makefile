# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgould <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/22 11:22:29 by mgould            #+#    #+#              #
#    Updated: 2017/04/26 14:19:21 by mgould           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = lem-in

LIB = thelibrary

LIBA = thelibrary/libft.a

CFLAGS = -g -Wall -Wextra -Werror -I $(LIB) -I .

OBJCS = main.o initstruct.o parseinput.o parserms.o parselnks.o \
		displaymap.o edgemap.o pathfind.o pathhelpers.o findroutes.o \
		initstruct1.o selectroute.o antmarch.o

all: $(NAME1)

$(NAME1): $(OBJCS) $(LIBA)
	gcc $(CFLAGS) -o $@ $^

$(LIBA): force
	cd $(LIB) && $(MAKE)

force:
	@true

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJCS)
	cd $(LIB) && make fclean

fclean: clean
	rm -f $(NAME1)

re: fclean all

.PHONY: clean re fclean
