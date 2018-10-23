# CPP_Arcade

This Epitech project was made in C++ by Corentin LEROY, Maxime GROSJEAN and Pierre BOUTEILLER.

# Core

To compile, use the following command:

    $> make core

# Libraries

There are two types of libraries: graphical libraries and game libraries.

## Graphical Libraries

To compile you will need 3 libraries:

	$> sudo apt-get install libncurses-5
	$> sudo apt-get install libsdl2-dev libsdl2-ttf-dev
	$> sudo apt-get install libsfml-dev

**Note:** The SFML version must be 2.3 to compile.

	$> make graphicals

To run the SFML and SDL libraries you will need a font named [Symtext](https://www.dafont.com/fr/symtext.font). It must be located at the following path:

	./cpp_arcade/resources/Symtext.ttf

## Game Libraries

To compile you must type this command:

	$> make games

# Commands

After compiling everything (you can use a simple "make" command) you can start the application with the following line:

	$> ./arcade <DYNAMIC_GRAPHICAL_LIBRARY_PATH>

**Note**: The libraries and the games must be stored in the "lib" and "games" folders.
