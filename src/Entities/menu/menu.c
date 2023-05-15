#include "menu.h"

int manageMenu(Framework *game, Menu* menu, Network *information, GameState *state, AddressBook *record) {
    TTF_Init();
    char* options[] = {"Host Game", "Join Game", "Quit"};
    Menu menus = {
        .options = options,
        .numOptions = 3,
        .optionWidth = 200,
        .optionHeight = 50,
        .optionSpacing = 10,
        .menuX = 480,
        .menuY = 477,
    };
    int selectedOption = displayMenu(game->renderer, &menus);
    switch (selectedOption) {
        case 0:
            setUpServer(information, record, 2000);
            *state = ONGOING;
            break;
        case 1:
            // options
            setUpClient(information, "127.0.0.1", 2000);
            *state = ONGOING;
            break;
        case 2:     
            game->quit = true;
            break;
        default:
            break;
    }
    return selectedOption;
    TTF_Quit();
}

int displayMenu(SDL_Renderer* renderer, Menu* menu) 
{
    TTF_Font* font = TTF_OpenFont("resources/font.ttf", 24);
    SDL_Surface* optionSurfaces[menu->numOptions];
    SDL_Rect optionRects[menu->numOptions];

    SDL_Color textColor = {000, 000, 000};
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    int maxOptionWidth = 0;
    int totalOptionHeight = 0;
    
    for (int i = 0; i < menu->numOptions; i++) 
    {
        optionSurfaces[i] = TTF_RenderText_Solid(font, menu->options[i], textColor);
        optionRects[i].x = 0;
        optionRects[i].y = totalOptionHeight;
        optionRects[i].w = optionSurfaces[i]->w;
        optionRects[i].h = optionSurfaces[i]->h;
        totalOptionHeight += optionRects[i].h + menu->optionSpacing;
        if (optionRects[i].w > maxOptionWidth) {
            maxOptionWidth = optionRects[i].w;
        }
    }

    SDL_Texture* imageTexture = IMG_LoadTexture(renderer, "resources/FINAL_menu2.png"); 

    int menuWidth = maxOptionWidth + menu->optionSpacing * 2;
    int menuHeight = totalOptionHeight - menu->optionSpacing;
    int menuX = 405;//(SCREEN_WIDTH - menuWidth) / 2 + 200; // Adjust center position to the side
    int menuY = 600;//(SCREEN_HEIGHT - menuHeight) / 2;

    for (int i = 0; i < menu->numOptions; i++) 
    {
        optionRects[i].x = menuX + (maxOptionWidth - optionRects[i].w) / 2;
        optionRects[i].y = menuY + optionRects[i].y;
    }

    int mouseX=0, mouseY=0; 
    int selectedOption = -1;
    SDL_Event event;
    
    while (selectedOption == -1) 
    {
        while (SDL_PollEvent(&event)) 
        {
            
            switch (event.type) 
            {
                case SDL_QUIT:
                    selectedOption = menu->numOptions - 1;
                    break;
                case SDL_MOUSEBUTTONUP:
                    
                    SDL_GetMouseState(&mouseX, &mouseY);
                    for (int i = 0; i < menu->numOptions; i++) 
                    {
                        if (SDL_PointInRect(&(SDL_Point){mouseX, mouseY}, &optionRects[i])) 
                        {
                            selectedOption = i;
                        }
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, imageTexture, NULL, NULL);

        for (int i = 0; i < menu->numOptions; i++) 
        {
            SDL_Texture* optionTexture = SDL_CreateTextureFromSurface(renderer, optionSurfaces[i]);
            SDL_RenderCopy(renderer, optionTexture, NULL, &optionRects[i]);
            SDL_DestroyTexture(optionTexture);
        }

        SDL_RenderPresent(renderer);
    }

    

    for (int i = 0; i < menu->numOptions; i++) 
    {
        SDL_FreeSurface(optionSurfaces[i]);
    }

    TTF_CloseFont(font);

    return selectedOption;
}