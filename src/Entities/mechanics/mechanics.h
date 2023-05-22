#ifndef MECHANICS_H
#define MECHANICS_H

#include <SDL2/SDL.h>

#include "../player/player.h"
#include "../perks/perks.h"
#define  Default_Speed 2

void HuntAndRevive(SDL_Renderer *renderer, Player players[]);
static void checkCapturedStatus(Player players[]);
static void handleCage(SDL_Renderer *renderer, Image *cage, Player players[]);

#endif