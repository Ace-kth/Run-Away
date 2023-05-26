#include "player.h"

static Player createPlayer(SDL_Renderer *renderer, char playerModel[], int playerNumber, int positionX, int positionY) {
    Player playerX;

    playerX.spriteSheetTexture = IMG_LoadTexture(renderer, playerModel);
    if (playerX.spriteSheetTexture == NULL) {
        printf("%s\n", SDL_GetError());
        exit(1);
    }

    int frame_count = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 3; x++) {
            playerX.spriteClip[frame_count].x = x * (PLAYER_FRAME_HEIGHT)+1;
            playerX.spriteClip[frame_count].y = y * (PLAYER_FRAME_WIDTH)+3;
            playerX.spriteClip[frame_count].w = PLAYER_FRAME_WIDTH;
            playerX.spriteClip[frame_count].h = PLAYER_FRAME_HEIGHT;
            frame_count++;
        }
    }

    playerX.down = false;
    playerX.up = false;
    playerX.left = false;
    playerX.right = false;

    playerX.position.x = positionX;
    playerX.position.y = positionY;
    playerX.position.w = PLAYER_FRAME_WIDTH;
    playerX.position.h = PLAYER_FRAME_HEIGHT;

    playerX.frame = 6;
    playerX.speed = Default_Speed;
    // playerX.speedBoostStartTime = 0;
    // playerX.baseSpeed = 2;
    // playerX.boostedSpeed = 4;

    playerX.player = playerNumber;
    playerX.captured = false;
    playerX.frozen = false;
    playerX.movementKeysReversed = false;
    return playerX;
}

void handlePlayerMovement(Player *playerX, Camera *camera) {
    if (!playerX->captured) {
        if (playerX->up) {
            if (!encountersForbiddenTile(playerX->position.x + (PLAYER_FRAME_WIDTH / 2), playerX->position.y, camera)) {
                playWalkingSound();
                // printf("Player: Up\n");
                // printf("X: %d, Y: %d\n", playerX->position.x, playerX->position.y);
                playerX->position.y -= playerX->speed;
                if (playerX->frame == 9 || playerX->frame == 10)
                    playerX->frame++;
                else
                    playerX->frame = 9;
            }
        }
        else if (playerX->down) {
            if (!encountersForbiddenTile(playerX->position.x + (PLAYER_FRAME_WIDTH / 2), playerX->position.y + PLAYER_FRAME_HEIGHT, camera)) {
                playWalkingSound();
                // printf("Player: Down\n");
                // printf("X: %d, Y: %d\n", playerX->position.x, playerX->position.y);
                playerX->position.y += playerX->speed;
                if (playerX->frame == 0 || playerX->frame == 1)
                    playerX->frame++;
                else
                    playerX->frame = 0;
            }
        }
        if (playerX->left) {
            if (!encountersForbiddenTile(playerX->position.x, playerX->position.y + (PLAYER_FRAME_HEIGHT / 2), camera)) {
                playWalkingSound();
                // printf("Player: Left\n");
                // printf("X: %d, Y: %d\n", playerX->position.x, playerX->position.y);
                playerX->position.x -= playerX->speed;
                if (playerX->frame == 3 || playerX->frame == 4)
                    playerX->frame++;
                else
                    playerX->frame = 3;
            }
        }
        else if (playerX->right) {
            if (!encountersForbiddenTile(playerX->position.x + PLAYER_FRAME_WIDTH, playerX->position.y + (PLAYER_FRAME_HEIGHT / 2), camera)) {
                playWalkingSound();
                // printf("Player: Right\n");
                // printf("X: %d, Y: %d", playerX->position.x, playerX->position.y);
                playerX->position.x += playerX->speed;
                if (playerX->frame == 6 || playerX->frame == 7)
                    playerX->frame++;
                else
                    playerX->frame = 6;
            }
        }
    }
}

void renderPlayers(Framework game, Player players[], Camera camera) {
    for (int i = 0; players[i].player != 0; i++) {
        SDL_Rect playerPosition = players[i].position;
        playerPosition.x -= camera.x;
        playerPosition.y -= camera.y;
        SDL_RenderCopyEx(game.renderer, players[i].spriteSheetTexture, &players[i].spriteClip[players[i].frame], &playerPosition, 0, NULL, SDL_FLIP_NONE);
    }
}

static void handleKeyPresses(Framework *game, Player *playerX, Player *playerY, Player *playerZ) {
    SDL_Keycode key = game->event.key.keysym.sym;

    if (playerX->movementKeysReversed) {
        // Reverse movement keys for playerX
        if (key == SDLK_UP) {
            key = SDLK_DOWN;
        }
        else if (key == SDLK_DOWN) {
            key = SDLK_UP;
        }
        else if (key == SDLK_LEFT) {
            key = SDLK_RIGHT;
        }
        else if (key == SDLK_RIGHT) {
            key = SDLK_LEFT;
        }
    }

    if (playerY->movementKeysReversed) {
        // Reverse movement keys for playerY
        if (key == SDLK_w) {
            key = SDLK_s;
        }
        else if (key == SDLK_s) {
            key = SDLK_w;
        }
        else if (key == SDLK_a) {
            key = SDLK_d;
        }
        else if (key == SDLK_d) {
            key = SDLK_a;
        }
    }

    if (playerZ->movementKeysReversed) {
        // Reverse movement keys for playerZ
        if (key == SDLK_u) {
            key = SDLK_j;
        }
        else if (key == SDLK_j) {
            key = SDLK_u;
        }
        else if (key == SDLK_h) {
            key = SDLK_k;
        }
        else if (key == SDLK_k) {
            key = SDLK_h;
        }
    }

    switch (key) {
    case SDLK_UP:
        playerX->up = true;
        break;
    case SDLK_DOWN:
        playerX->down = true;
        break;
    case SDLK_LEFT:
        playerX->left = true;
        break;
    case SDLK_RIGHT:
        playerX->right = true;
        break;
    case SDLK_w:
        playerY->up = true;
        break;
    case SDLK_s:
        playerY->down = true;
        break;
    case SDLK_a:
        playerY->left = true;
        break;
    case SDLK_d:
        playerY->right = true;
        break;
    case SDLK_u:
        playerZ->up = true;
        break;
    case SDLK_j:
        playerZ->down = true;
        break;
    case SDLK_h:
        playerZ->left = true;
        break;
    case SDLK_k:
        playerZ->right = true;
        break;
    case SDLK_m:
        game->isMuted = !game->isMuted;
        if (game->isMuted) {
            Mix_VolumeMusic(0);
        }
        else {
            Mix_VolumeMusic(MIX_MAX_VOLUME);
        }
        break;
    case SDLK_ESCAPE:
        game->quit = true;
        break;
    default:
        break;
    }
}

static void handleKeyReleases(Framework *game, Player *playerX, Player *playerY, Player *playerZ) {
    SDL_Keycode key = game->event.key.keysym.sym;

    if (playerX->movementKeysReversed) {
        // Reverse movement keys for playerX
        if (key == SDLK_UP) {
            key = SDLK_DOWN;
        }
        else if (key == SDLK_DOWN) {
            key = SDLK_UP;
        }
        else if (key == SDLK_LEFT) {
            key = SDLK_RIGHT;
        }
        else if (key == SDLK_RIGHT) {
            key = SDLK_LEFT;
        }
    }

    if (playerY->movementKeysReversed) {
        // Reverse movement keys for playerY
        if (key == SDLK_w) {
            key = SDLK_s;
        }
        else if (key == SDLK_s) {
            key = SDLK_w;
        }
        else if (key == SDLK_a) {
            key = SDLK_d;
        }
        else if (key == SDLK_d) {
            key = SDLK_a;
        }
    }

    if (playerZ->movementKeysReversed) {
        // Reverse movement keys for playerZ
        if (key == SDLK_u) {
            key = SDLK_j;
        }
        else if (key == SDLK_j) {
            key = SDLK_u;
        }
        else if (key == SDLK_h) {
            key = SDLK_k;
        }
        else if (key == SDLK_k) {
            key = SDLK_h;
        }
    }

    switch (key) {
    case SDLK_UP:
        playerX->up = false;
        break;
    case SDLK_DOWN:
        playerX->down = false;
        break;
    case SDLK_LEFT:
        playerX->left = false;
        break;
    case SDLK_RIGHT:
        playerX->right = false;
        break;
    case SDLK_w:
        playerY->up = false;
        break;
    case SDLK_s:
        playerY->down = false;
        break;
    case SDLK_a:
        playerY->left = false;
        break;
    case SDLK_d:
        playerY->right = false;
        break;
    case SDLK_u:
        playerZ->up = false;
        break;
    case SDLK_j:
        playerZ->down = false;
        break;
    case SDLK_h:
        playerZ->left = false;
        break;
    case SDLK_k:
        playerZ->right = false;
        break;
    default:
        break;
    }
}



void handleInput(Framework *game, Player *playerX, Player *playerY, Player *playerZ) {
    while (SDL_PollEvent(&game->event)) {
        if (game->event.type == SDL_QUIT) {
            game->quit = true;
        }
        else if (game->event.type == SDL_KEYDOWN) {
            handleKeyPresses(game, playerX, playerY, playerZ);
        }
        else if (game->event.type == SDL_KEYUP) {
            handleKeyReleases(game, playerX, playerY, playerZ);
        }
    }
}

void loadPlayers(SDL_Renderer *renderer, Player players[]) {
    players[0] = createPlayer(renderer, "resources/Hunter.png", 1, 820, 460);
    players[1] = createPlayer(renderer, "resources/Hunter_2.png", 2, 1300, 780);
    players[2] = createPlayer(renderer, "resources/Runner_2.png", 3, 900, 1070);
    //players[3] = createPlayer(renderer, "resources/Runner_3.png", 3, 2050, 1070);
}