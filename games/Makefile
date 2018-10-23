##
## EPITECH PROJECT, 2018
## arcade
## File description:
## Makefile
##

CXX		=	g++

CPPFLAGS	+=	-W -Wall -Wextra -fPIC -I ../include -std=c++11 -g

RM		=	rm -f

PREFIX		=	lib_arcade_

# NIBBLER		=	$(PREFIX)nibbler.so

# SRC_NIBBLER	=	./nibbler/NibblerGame.cpp	\
# 			./nibbler/entryPoint.cpp

# NIBBLER_OBJ	=	$(SRC_NIBBLER:.cpp=.o)

SOLARFOX	=	$(PREFIX)solarfox.so

SRC_SOLARFOX	=	./solarfox/SolarFoxGame.cpp	\
			./solarfox/Player.cpp		\
			./solarfox/Beam.cpp		\
			./solarfox/Enemy.cpp		\
			./solarfox/entryPoint.cpp

SOLARFOX_OBJ	=	$(SRC_SOLARFOX:.cpp=.o)

PACMAN		=	$(PREFIX)pacman.so

SRC_PACMAN	=	./pacman/PacmanGame.cpp	\
			./pacman/Enemy.cpp	\
			./pacman/ACharacter.cpp	\
			./pacman/entryPoint.cpp

PACMAN_OBJ	=	$(SRC_PACMAN:.cpp=.o)

OBJ		=	$(PACMAN_OBJ)		\
			$(SOLARFOX_OBJ)		\
#			$(NIBBLER_OBJ)

NAMES		=	$(PACMAN)		\
			$(SOLARFOX)		\
#			$(NIBBLER)

all:	$(PACMAN) $(SOLARFOX) # $(NIBBLER)

# $(NIBBLER):	$(NIBBLER_OBJ)
# 	$(CXX) -shared -o $(NIBBLER) $(NIBBLER_OBJ)

$(SOLARFOX):	$(SOLARFOX_OBJ)
	$(CXX) -shared -o $(SOLARFOX) $(SOLARFOX_OBJ)

$(PACMAN):	$(PACMAN_OBJ)
	$(CXX) -shared -o $(PACMAN) $(PACMAN_OBJ)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAMES)

re:	fclean all

.PHONY:	all clean fclean re
