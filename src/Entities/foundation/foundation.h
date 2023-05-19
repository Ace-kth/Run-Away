#ifndef FOUNDATION_H
#define FOUNDATION_H

#include <stdbool.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_ttf.h>

#include "../audio/audio.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 900

#define FPS 60

#define TIMER_LENGTH 1000

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    TTF_Font *font;
    SDL_Event event;
    bool isMuted;
    bool quit;
} Framework;

typedef struct {
    bool active;
    SDL_Texture* texture;
    SDL_Rect rectangle;
} Image;

typedef struct {
    time_t timeWhenStarting;
    double timeRemaining;
    int minutesRemaining;
    int secondsRemaining;
} Timer;

void initialize(Framework *game);
void manageFrameRate(int timeAtLoopBeginning);
void manageTimer(Framework *game, Timer *timerData);
static void calculateRemainingTime(Timer *timerData);
static void displayTime(Framework *game, Timer *timerData);
static void checkIfTimerHasExpired(bool *quit, Timer *timerData);
static void drawRectangle(SDL_Renderer *renderer, int x, int y, int w, int h);

#endif