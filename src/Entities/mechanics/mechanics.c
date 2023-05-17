#include "mechanics.h"

void HuntAndRevive(SDL_Renderer *renderer, Player players[]) {
    static Image cage = {0, NULL, {0, 0, 40, 40}};
    checkCapturedStatus(players);
    handleCage(renderer, &cage, players);
}

static void handleCage(SDL_Renderer *renderer, Image *cage, Player players[]) {
    for (int i = 0; players[i].player != 0; i++) {
        if (players[i].speed == 0) {
            if (!cage->active) {
                cage->texture = IMG_LoadTexture(renderer,"resources/cage.png");
                cage->active = true;
            }
            if (players[i].captured) {
                cage->rectangle.x = (players[i].position.x-7); // -7 så att spelaren blir exakt i mitten av "cage"
                cage->rectangle.y = (players[i].position.y-2);
                SDL_RenderCopy(renderer, cage->texture, NULL, &cage->rectangle);
            }
        }
    }
    
    if (cage->active) {
        int numberOfCapturedPlayers;
        for (int i = 0; players[i].player != 0; i++) {
            if (players[i].speed == 0) {
                numberOfCapturedPlayers++;
            }
        }
        if (numberOfCapturedPlayers == 0) {
            SDL_DestroyTexture(cage->texture);
            cage->active = false;
        }
    }
}

static void checkCapturedStatus(Player players[]) {
    for (int i = 0; players[i].player != 0; i++) {
        if (players[i].player == 2) {
            continue;
        }
        else {
            if (checkCollision(players[i].position, players[1].position) && players[i].captured == false) {
                playCageLockSound();
                players[i].captured = true;
                players[i].speed = 0;
                players[i].frame = 1;
            }
            else if (checkCollision(players[0].position, players[2].position)) {
                if (players[0].captured == true || players[2].captured == true) {
                    playCageUnlockSound();
                    players[0].speed = 2;
                    players[0].captured = false;
                    players[2].speed = 2;
                    players[2].captured = false;
                }
            }
        }
    }
}