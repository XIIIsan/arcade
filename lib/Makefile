##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

CXX		=	g++

CPPFLAGS	+=	-W -Wall -Wextra -I ../include -std=c++11 -fPIC -g

RM		=	rm -f

PREFIX		=	lib_arcade_

SDL		=	$(PREFIX)sdl2.so

SRC_SDL		=	./sdl2/SDL2GraphicLib.cpp	\
			./sdl2/entryPoint.cpp

SDL_OBJ		=	$(SRC_SDL:.cpp=.o)

SDL_FLAGS	=	-lSDL2 -lSDL2main -lSDL2_ttf

NCURSE		=	$(PREFIX)ncurse.so

SRC_NCURSE	=	./ncurse/NCursesGraphicLib.cpp	\
			./ncurse/entryPoint.cpp

NCURSE_OBJ	=	$(SRC_NCURSE:.cpp=.o)

NCURSE_FLAGS	=	-lncurses

SFML		=	$(PREFIX)sfml.so

SRC_SFML	=	./sfml/SFMLGraphicLib.cpp	\
			./sfml/entryPoint.cpp

SFML_OBJ	=	$(SRC_SFML:.cpp=.o)

SFML_FLAGS	=	-lsfml-window -lsfml-graphics -lsfml-system


OBJ		=	$(SDL_OBJ)	\
			$(SFML_OBJ)	\
			$(NCURSE_OBJ)	\

NAMES		=	$(SDL)		\
			$(SFML)		\
			$(NCURSE)

all:	$(SDL) $(SFML) $(NCURSE)

$(SDL):		$(SDL_OBJ)
	$(CXX) -shared -o $(SDL) $(SDL_OBJ) $(SDL_FLAGS)

$(SFML):	$(SFML_OBJ)
	$(CXX) -shared -o $(SFML) $(SFML_OBJ) $(SFML_FLAGS)

$(NCURSE):	$(NCURSE_OBJ)
	$(CXX) -shared -o $(NCURSE) $(NCURSE_OBJ) $(NCURSE_FLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAMES)

re:	fclean all

.PHONY:	all clean fclean re
