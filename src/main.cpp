#include <iostream>
#include "../include/init.h"


#define alredy_game true // Si un jeu et deja chargé au lancement
#define game_name "4-flags.ch8"// Nom du jeu qui sera deja chargé
#define Step_par_Step true // Si le jeu fontione etape par etape


int main (int argc, char** argv) {

Chip8 chip8 = Chip8(); 

chip8.Emulation(argc, argv, alredy_game, game_name, Step_par_Step);
}