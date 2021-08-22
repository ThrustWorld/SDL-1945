#include "gameobject.h"
#include "bullet.h"

GameObject* NewGameObject(Point* pos, Size* texture_size, char* texture_path){
    GameObject* go = (GameObject*)calloc(1, sizeof(GameObject));
    go->position = pos;
    go->texture_path = texture_path;
    go->texture_size = texture_size;
    go->IsActive = true;
    go->MyRect = NewRect(go->position, go->texture_size);
    return go;
}

void DestroyGameObject(GameObject* go){
    if (go)
    {
        DestroyPoint(go->position);
        DestroySize(go->texture_size);
        free(go);
    }
}

void RenderGameObject(SDL_Renderer* render, GameObject* go){
    SDL_Texture* texture = NewTexture(render, go->texture_path);
    if (texture == NULL)
    {
        printf("texture '%s' is null", go->texture_path);
    }
    else{
        if (go->IsActive)
        {
            RenderingTexture(render, texture, go->position, go->texture_size);
        }
    }
    SDL_DestroyTexture(texture);
    //SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "render_go: %f, %f", go->position.x, go->position.y);
}

void GenericAddElemList(List* l, int n, char* elem, int type){
    if (!strcmp("bullet", elem))
    {
        for (int i = 0; i < n; i++)
        {
            AddElemList(l, NewBullet((BulletType)type));
            //printf("bullet[%d][%d]\n", i, type);
        }   
    }
    else if (!strcmp("island", elem)){
        for (int i = 0; i < n; i++)
        {
            AddElemList(l, NewIsland((IslandsType)type));
        }
    }
    else if (!strcmp("background", elem)){
        for (int i = 0; i < n; i++)
        {
            AddElemList(l, NewGameObject(NewPoint(0, 540-HEIGHT_WINDOW), NewSize(WIDTH_WINDOW, HEIGHT_WINDOW*2), (char*)"./assets/map/water2.png"));
        }
    }
}

GameObject* NewIsland(IslandsType it){
    GameObject* go;
    if(it == Normal)
    {
        Size* s = NewSize(70,80);
        go = NewGameObject(RandomPoint(s), s, (char*)"./assets/map/island1.png");
    }
    else if(it == Vulcan)
    {
        Size* s = NewSize(80,80);
        go = NewGameObject(RandomPoint(s), s, (char*)"./assets/map/island2.png");
    }
    else if(it == Sand)
    {
        Size* s = NewSize(70,90);
        go = NewGameObject(RandomPoint(s), s, (char*)"./assets/map/island3.png");
    }
    go->IsActive = true;
    return go;
}

void RenderGameObjectList(SDL_Renderer* renderer, List* goList, boolean bg, float deltaTime)
{
    int speed = 40;
    int count = 0;
    Node* each = goList->__head;
    GameObject* free_GO;
    while (each)
    {
        Node* next = each->next;
        if(((GameObject*)each->data)->IsActive == true){
            free_GO = (GameObject*)each->data;
            free_GO->position->y += 1 * speed * deltaTime;
            RenderActiveGameObject(renderer, free_GO, bg);
        }
        count++;
        each = next;
    }
    each = NULL;
    free_GO = NULL;
}

void RenderActiveGameObject(SDL_Renderer* renderer, GameObject* go, boolean bg)
{
    if (!bg && go->position->y > (HEIGHT_WINDOW - 100) + go->texture_size->Height)
    {
        go->position = RandomPoint(go->texture_size);
        //printf("not bg but normal go\n");
    }
    else if (bg && go->position->y > - 10){
        go->position->y = 540-go->texture_size->Height;
        //printf("bg replaced\n");
    }
    else{
        RenderGameObject(renderer, go);
        //printf("render go\n");
    }
}