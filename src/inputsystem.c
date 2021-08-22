#include <inputsystem.h>

void init_buttons(InputSystem* inputsys, char* system_movement){
    if (!strcmp(system_movement, "wasd"))
    {
        //printf("WASD buttons selected.\n");
        inputsys->up = SDL_SCANCODE_W;
        inputsys->left = SDL_SCANCODE_A;
        inputsys->down = SDL_SCANCODE_S;
            inputsys->right = SDL_SCANCODE_D;
        inputsys->shoot = SDL_SCANCODE_SPACE;
    }
    else if (!strcmp(system_movement, "arrow"))
    {
        //printf("ARROWS buttons selected.\n");
        inputsys->up = SDL_SCANCODE_UP;
        inputsys->left = SDL_SCANCODE_LEFT;
        inputsys->down = SDL_SCANCODE_DOWN;
        inputsys->right = SDL_SCANCODE_RIGHT;
        inputsys->shoot = SDL_SCANCODE_SPACE;
    }
}

InputSystem* NewInputSystem(char* system_buttons){
    InputSystem* input_ = (InputSystem*)calloc(1, sizeof(InputSystem));
    input_->IsActive = true;
    input_->explosion = Mix_LoadWAV("./assets/audio/snd_explosion1.wav");
    Mix_VolumeChunk(input_->explosion, SDL_MIX_MAXVOLUME / 8);
    init_buttons(input_, system_buttons);
    return input_;
}

void DestroyInputSystem(InputSystem* input_){
    Mix_FreeChunk(input_->explosion);
    free(input_);
}

boolean UpdateInputSystem(SDL_Event* event, InputSystem* inputSys, Character* c, double delta_time){
    while (SDL_PollEvent(event)){
        if (event->type == SDL_QUIT) {
                free(event);
                return true;
            }
        Movement(event, inputSys, c, delta_time);
    }
    return false;
}

void Movement(SDL_Event* event, InputSystem* inputSys, Character* c, double delta_time){
    if(inputSys->IsActive){
        if (event->type == SDL_KEYDOWN)
        {
            if(event->key.keysym.scancode == inputSys->up){  // up
                if (c->Go->position->y > 0)
                {
                    c->Go->position->y += -1 * c->Speed * delta_time;
                }
                else{
                    c->Go->position->y = 0;
                }
            }
            if(event->key.keysym.scancode == inputSys->left){  // left
                if (c->Go->position->x > 0)
                {
                    c->Go->position->x += -1 * c->Speed * delta_time;
                }
                else{
                    c->Go->position->x = 0;
                }
            }
            if(event->key.keysym.scancode == inputSys->down){  // down
                if (c->Go->position->y < (HEIGHT_WINDOW - 95) - c->Go->texture_size->Height)
                {
                    c->Go->position->y += 1 * c->Speed * delta_time;
                }
                else{
                    c->Go->position->y = (HEIGHT_WINDOW - 95) - c->Go->texture_size->Height;
                }
            }
            if(event->key.keysym.scancode == inputSys->right){  // right
                if (c->Go->position->x < WIDTH_WINDOW - c->Go->texture_size->Width)
                {
                    c->Go->position->x += 1 * c->Speed * delta_time;
                }
                else{
                    c->Go->position->x = WIDTH_WINDOW - c->Go->texture_size->Width;
                }
            }
            if(event->key.keysym.scancode == inputSys->shoot){  // shoot
                shoot(c);
                Mix_PlayChannel(-1, inputSys->explosion, 0);
            }

        }
    }
}

void shoot (Character* c){
    if (c->Go->position->y > 0)
    {
        int count = 0;
        int index = 0;
        Node* each = c->bullets->__head;
        Bullet* bullet_app;
        while (each)
        {
            Node* next = each->next;
            if (((Bullet*)each->data)->Go->IsActive == false)
            {
                bullet_app = ((Bullet*)each->data); 
                bullet_app->Go->IsActive = true;
                bullet_app->Go->position->x = c->Go->position->x + (c->Go->texture_size->Width * 0.5f) - (bullet_app->Go->texture_size->Width * 0.5f);
                bullet_app->Go->position->y = c->Go->position->y + bullet_app->Go->texture_size->Height;
                index = count;
                //printf("count: %d\nactive: %d\n", index, (int)((Bullet*)each->data)->Go->IsActive);
                break;
            }
            count++;
            each = next;
        }
        each = NULL;
        bullet_app = NULL;
    }
}