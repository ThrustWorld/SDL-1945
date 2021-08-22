#include <renderer.h>

// texture
int RenderingTexture(SDL_Renderer* renderer, SDL_Texture* tex, Point* p, Size* s){
    SDL_Rect* rect = NewRect(p,s);
    int res =  SDL_RenderCopy(renderer, tex, NULL, rect);
    DestroyRect(rect);
    return res;
}

int RenderingPath(SDL_Renderer* renderer, char* path, Point* p, Size* s){
    SDL_Texture* t = NewTexture(renderer, path);
    int res = RenderingTexture(renderer, t, p, s);
    SDL_DestroyTexture(t);
    return res;
}

SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file){
    return (SDL_Texture*)IMG_LoadTexture(renderer, path_file); 
}

SDL_Rect* NewRect(Point* p, Size* s){
    SDL_Rect* rect_ = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
    //printf("-------\nSize -> rect w: %f h: %f \n", s->Width, s->Height);
    //printf("Pos -> rect x: %f y: %f \n", p->x, p->y);
    rect_->x = p->x;
    rect_->y = p->y; 
    rect_->w = s->Width; 
    rect_->h = s->Height;
    // printf("\nSize -> rect w: %d h: %d \n", rect_->w, rect_->h);
    // printf("Pos -> rect x: %d y: %d \n-------\n", rect_->x, rect_->y);
    return rect_;
}

void DestroyRect(SDL_Rect* rect){
    free(rect);
}

// animation
Animator* NewAnimator(){
    Animator* animator = (Animator*)calloc(1,(sizeof(Animator)));
    animator->Animations = NewList();
    return animator;
}

void DestroyAnimator(Animator* animator){
    DestroyListAnimation(animator->Animations);
    free(animator);
}

Animation* NewAnimation(char* name_animation, char* texture_path, SDL_Rect* src, int nFrames, double TimeFrame){
    Animation* animation = (Animation*)calloc(1,(sizeof(Animation)));

    animation->Name = name_animation;
    animation->currFrame = 0;
    animation->TotFrames = nFrames;
    animation->DelayFrame = TimeFrame;
    animation->TimeFrame = TimeFrame;
    animation->texture_path = texture_path;
    animation->FrameSize = NewSize(src->w , src->h);
    animation->list = NewList();
    for (int i = 0; i < animation->TotFrames; i++){
        AddElemList(animation->list, NewRect(NewPoint(src->w * i,src->y), animation->FrameSize));
    };
    return animation;
}

void DestroyListAnimation(List* animations){
    Node* each = animations->__head;
    while (each)
    {
        Node* next = each->next;
        DestroyAnimation(((Animation*)each->data));
        each = next;
    }
    each = NULL;
}

void DestroyAnimation(Animation* anim){
    DestroySize(anim->FrameSize);
    DestroyList(anim->list);
    free(anim);
}

boolean RenderingThisAnimation(SDL_Renderer* r, Animator* anim, char* animation_name, Point* p, double deltatime){
    int count = 0;
    boolean finished = false;
    Node* each = anim->Animations->__head;
    Animation* anim_app;
    while (each)
    {
        Node* next = each->next;
        if(!strcmp(((Animation*)each->data)->Name, animation_name)){
            //printf("\nanimation_name: %s\n", animation_name);
            anim_app = ((Animation*)each->data);
            finished = RenderingListAnimation(r, anim_app, NewRect(p,anim_app->FrameSize), deltatime);
            break;
        }
        count++;
        each = next;
    }
    each = NULL;
    anim_app = NULL;
    return finished;
}

boolean RenderingListAnimation(SDL_Renderer* r, Animation* anim, SDL_Rect* dst, double deltatime){
    int count = 0;
    Node* each = anim->list->__head;
    boolean first = true;
    boolean finished = false;
    SDL_Rect* last;
    while (each)
    {
        Node* next = each->next;
        if(count == anim->currFrame){
            //printf("animation_frame: %d\n", anim->currFrame);
            if (anim->TimeFrame > 0)
            {
                anim->TimeFrame -= deltatime;
                //printf("\ndeltatime: %f \nframe: %d \ndelay_frame: %f\n", deltatime, anim->currFrame, anim->TimeFrame);
            }
            else{
                last = (SDL_Rect*)each->data;
                if (anim->currFrame == (anim->TotFrames - 1))
                {
                    finished = true;
                }
                anim->currFrame = (anim->currFrame < (anim->TotFrames - 1)) ? anim->currFrame + 1 : 0;
                anim->TimeFrame = anim->DelayFrame;
                //printf("\nsrc changed\ncurr_frame: %d \ndelay restart %f\n", anim->currFrame, anim->TimeFrame);
            }
            if (first)
            {
                last = (SDL_Rect*)each->data;
                RenderingAnimation(r,anim->texture_path,last,dst);
                first = false;
            }
            else{
                RenderingAnimation(r,anim->texture_path,last,dst);
            }
        }
        count++;
        each = next;
    }
    each = NULL;
    last = NULL;
    return finished;
}

void RenderingAnimation(SDL_Renderer* r, char* t_p, SDL_Rect* src, SDL_Rect* dst){
    // printf("SRC x: %d y: %d  \t w: %d h:%d\n",src->x,src->y,src->w,src->h);
    // printf("DST x: %d y: %d  \t w: %d h:%d\n",dst->x,dst->y,dst->w,dst->h);
    // printf("path: %s\n", t_p);
    SDL_Texture* t = NewTexture(r,t_p);
    if (t == NULL)
    {
        printf("non ce n'e' texture\n");
    }
    //NewRect(NewPoint(10,10), NewSize(65,65))
    SDL_RenderCopy(r,t,src,dst);
    SDL_DestroyTexture(t);
}

// windows
void CloseWindow(SDL_Renderer* r, SDL_Window* win){
    TTF_Quit();
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
}