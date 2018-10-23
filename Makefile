##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

CXX		=	g++

NAME		=	arcade

CPPFLAGS	+=	-W -Wall -Wextra -I./include --std=c++11 -g

LDFLAGS		=	-ldl -rdynamic

LIBSDIR		=	./lib/

GAMESDIR	=	./games/

RM		=	rm -f

SRC		=	src/main.cpp		\
			src/FileManager.cpp	\
			src/Core.cpp		\
			src/Menu.cpp		\
			utils/PixelBox.cpp	\
			utils/Color.cpp		\
			utils/TextBox.cpp

OBJ		=	$(SRC:.cpp=.o)

all:	core graphicals games

core:	$(NAME)

$(NAME):	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean core

games:
	make -C $(GAMESDIR)

clean_games:
	make -C $(GAMESDIR) clean

fclean_games:
	make -C $(GAMESDIR) fclean

re_games:
	make -C $(GAMESDIR) re

graphicals:
	make -C $(LIBSDIR)

clean_graphicals:
	make -C $(LIBSDIR) clean

fclean_graphicals:
	make -C $(LIBSDIR) fclean

re_graphicals:
	make -C $(LIBSDIR) re

clean_all: clean clean_graphicals clean_games

fclean_all: fclean fclean_graphicals fclean_games

re_all: re re_graphicals re_games

.PHONY:	all core clean fclean re games clean_games fclean_games re_games graphicals clean_graphicals fclean_graphicals re_graphicals clean_all fclean_all re_all
