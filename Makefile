# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 10:21:07 by kferterb          #+#    #+#              #
#    Updated: 2022/10/14 10:21:08 by kferterb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= program

SRC		=	main.cpp

OBJ		= $(SRC:.cpp=.o)

HEADR	=	other_tools/pair.hpp\
			other_tools/red_black_tree.hpp\
			other_tools/lexicographical_compare.hpp\
			other_tools/equal.hpp\
			other_tools/enable_integral.hpp\
			iterators/iterators_traits.hpp\
			iterators/node_iterator.hpp\
			iterators/reverse_iterator.hpp\
			iterators/vector_iterator.hpp\
			vector/vector.hpp\
			map/map.hpp\
			stack/stack.hpp\
			set/set.hpp

CC		= c++

CFLAGS	= -Wall -Wextra -Werror -std=c++98

all		: $(NAME)

$(NAME)	: $(OBJ) $(HEADR)
		$(CC) $(CFAGS) $(OBJ) -o $(NAME)

.cpp.o	: $(HEADR)
		$(CC) $(CFLAGS) -c $< -o $@

clean	:
		rm -f $(OBJ)

fclean	: clean
		rm -f $(NAME)

re		: fclean all

.PHONY	: clean fclean re all