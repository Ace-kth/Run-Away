#include "player.h"

Player createPlayer(SDL_Renderer *renderer, char playerModel[], int positionX, int positionY) {
    Player playerX;

    playerX.spriteSheetTexture = IMG_LoadTexture(renderer, playerModel);
    if (playerX.spriteSheetTexture == NULL) {
        printf("%s\n", SDL_GetError());
        exit(1);
    }

    int frame_count = 0;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 3; x++) {
            playerX.spriteClip[frame_count].x = x * (PLAYER_FRAME_HEIGHT) + 1; // 32 width/height
            playerX.spriteClip[frame_count].y = y * (PLAYER_FRAME_WIDTH) + 3;
            playerX.spriteClip[frame_count].w = PLAYER_FRAME_WIDTH;
            playerX.spriteClip[frame_count].h = PLAYER_FRAME_HEIGHT;
            frame_count++;
        }
    }

    playerX.down = false;
    playerX.up = false;
    playerX.left = false;
    playerX.right = false;

    playerX.position.x = positionX; //(positionX - PLAYER_FRAME_WIDTH) / 2;
    playerX.position.y = positionY; //(positionY - PLAYER_FRAME_HEIGHT) / 2;
    playerX.position.w = PLAYER_FRAME_WIDTH;
    playerX.position.h = PLAYER_FRAME_HEIGHT;

    playerX.frame = 6;
    playerX.speed = 2;

    return playerX;
}

void handlePlayerMovement(Player *playerX) {
    if (playerX->up) {
        if (!encountersForbiddenTile(playerX->position.x + (PLAYER_FRAME_WIDTH / 2), playerX->position.y)) {
            printf("Player: Up\n");
            printf("X: %d, Y: %d\n", playerX->position.x, playerX->position.y);
            playerX->position.y -= playerX->speed;
            if (playerX->frame == 9 || playerX->frame == 10)
                playerX->frame++;
            else
                playerX->frame = 9;
        }
    }
    else if (playerX->down) {
        if (!encountersForbiddenTile(playerX->position.x + (PLAYER_FRAME_WIDTH / 2), playerX->position.y + PLAYER_FRAME_HEIGHT)) {
            printf("Player: Down\n");
            printf("X: %d, Y: %d\n", playerX->position.x, playerX->position.y);
            playerX->position.y += playerX->speed;
            if (playerX->frame == 0 || playerX->frame == 1)
                playerX->frame++;
            else
                playerX->frame = 0;
        }
    }
    if (playerX->left) {
        if (!encountersForbiddenTile(playerX->position.x, playerX->position.y + (PLAYER_FRAME_HEIGHT / 2))) {
            printf("Player: Left\n");
            printf("X: %d, Y: %d\n", playerX->position.x, playerX->position.y);
            playerX->position.x -= playerX->speed;
            if (playerX->frame == 3 || playerX->frame == 4)
                playerX->frame++;
            else
                playerX->frame = 3;
        }
    }
    else if (playerX->right) {
        if (!encountersForbiddenTile(playerX->position.x + PLAYER_FRAME_WIDTH, playerX->position.y + (PLAYER_FRAME_HEIGHT / 2))) {
            printf("Player: Right\n");
            printf("X: %d, Y: %d", playerX->position.x, playerX->position.y);
            playerX->position.x += playerX->speed;
            if (playerX->frame == 6 || playerX->frame == 7)
                playerX->frame++;
            else
                playerX->frame = 6;
        }
    }
}