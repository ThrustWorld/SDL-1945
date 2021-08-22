//Per dire a SDL che si usera' il proprio main applicativo.
//Altrimenti SDL cerca di caricare il main da SDL2Main.lib
//NOTA: Si può passare anche come argomento di compilazione con -D
#define SDL_MAIN_HANDLED
#include "player.h"
#include "enemy.h"
#include "ui.h"
#include "physics.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    if(TTF_Init()){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize font: %s\n", SDL_GetError());
        return 1;
    }

    Size* win = NewSize(WIDTH_WINDOW, HEIGHT_WINDOW);

    SDL_Window* window = SDL_CreateWindow(
        "1945",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        win->Width,
        win->Height,
        0
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface* favicon = IMG_Load("./assets/ui/icon.png");
    SDL_SetWindowIcon(window, favicon);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
        return 2;
    }

    Uint64 curr_count = SDL_GetPerformanceCounter();
    Uint64 last_count = curr_count;
    double delta_time = 0.f;

    char title[100];
    float update_time = 0.f;

    Player* player = NewPlayer(NewPoint(290,180), NewSize(65,65), NewInputSystem((char*)"wasd"),100, 1000, (char*)"./assets/player/myplane_strip3.png");

    EnemyManager* enemymgr = NewEnemyManager();
    AddEnemyManagerList(enemymgr, NewSize(32,32), (char*)"./assets/enemy/enemy1_strip3.png", 5);
    AddEnemyManagerList(enemymgr, NewSize(32,32), (char*)"./assets/enemy/enemy2_strip3.png", 2);
    AddEnemyManagerList(enemymgr, NewSize(32,32), (char*)"./assets/enemy/enemy3_strip3.png", 10);

    PhysicsManager* physicsManager = NewPhysicsManager(player, enemymgr);

    Interface* ui = NewInterface();
    AddUiList(ui, NewPoint(0,HEIGHT_WINDOW-99), NewSize(WIDTH_WINDOW, 100), (char*)"./assets/ui/bottom.png");

    List* Islands = NewList();
    GenericAddElemList(Islands, 2, (char*)"island", Normal);
    GenericAddElemList(Islands, 2, (char*)"island", Vulcan);
    GenericAddElemList(Islands, 2, (char*)"island", Sand);

    List* Water = NewList();
    GenericAddElemList(Water, 1, (char*)"background", 0);

    boolean done = false;

    // soundtrack
    Mix_Music* soundTrack = Mix_LoadMUS("./assets/audio/background.mp3");
    Mix_AllocateChannels(2);
    
    Mix_VolumeMusic(SDL_MIX_MAXVOLUME/20);
    Mix_PlayMusic(soundTrack, -1);

    // explosion player
    // Mix_Chunk* explosion1 = Mix_LoadWAV("./assets/audio/snd_explosion1.wav");
    // Mix_VolumeChunk(explosion1, SDL_MIX_MAXVOLUME / 4);
    //Mix_PlayChannel(-1, explosion1, 0);
    
    // explosion enemy
    // Mix_Chunk* explosion2 = Mix_LoadWAV("./assets/audio/snd_explosion2.wav");
    // Mix_VolumeChunk(explosion2, SDL_MIX_MAXVOLUME / 10);
    //Mix_PlayChannel(-1, explosion2, 0);

    SDL_Event* event = (SDL_Event*)calloc(1, sizeof(SDL_Event));
    while (!done) {
        SDL_RenderFlush(renderer);
        SDL_RenderClear(renderer);

        // DELTATIME
        last_count = curr_count;
        curr_count = SDL_GetPerformanceCounter();
        delta_time = (float)(curr_count - last_count) / (float)SDL_GetPerformanceFrequency();
        int fps = (int)(1.f / delta_time);

        update_time += delta_time;
        if (update_time >= 1.f) {
            update_time -= 1.f;
            sprintf_s(title, sizeof(title), "1945 - Delta Time: %.6f - Fps: %d", delta_time, fps);
            SDL_SetWindowTitle(window, title);
        }

        // BACKGROUND
        RenderGameObjectList(renderer, Water, true, delta_time);
        RenderGameObjectList(renderer, Islands, false, delta_time);

        // PHYSICS
        CheckCollision(physicsManager);

        // ENEMY
        UpdateEnemyManager(renderer, enemymgr, delta_time);

        // UI BASE
        UpdateInterface(renderer, ui, delta_time);

        // PLAYER (INPUT, BULLETS, LIFE MANAGER)
        done = UpdatePlayer(renderer, event, player, delta_time);
        
        // BLIT
        SDL_RenderPresent(renderer);
    }

    //CLEAN UP
    CloseWindow(renderer, window);
    SDL_FreeSurface(favicon);
    DestroyPlayer(player);
    DestroyEnemyManager(enemymgr);
    DestroyPhysicsManager(physicsManager);
    DestroyInterface(ui);
    DestroyList(Islands);
    DestroyList(Water);

    Mix_FreeMusic(soundTrack);
    Mix_CloseAudio();

    return 0;
}