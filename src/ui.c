#include "ui.h"

Interface* NewInterface(){
    Interface* i = (Interface*)calloc(1,sizeof(Interface));
    i->UiList = NewList();
    return i;
}

void AddUiList(Interface* i, Point* p, Size* s, char* texture_path){
    AddElemList(i->UiList, NewUI(p,s,texture_path));
}

UI* NewUI(Point* p, Size* s, char* texture_path){
    UI* ui = (UI*)calloc(1,sizeof(UI));
    ui->txt_path = texture_path;
    ui->position = p;
    ui->size = s;
    return ui;
}

void UpdateInterface(SDL_Renderer* renderer, Interface* i, double dt){
    Node* each = i->UiList->__head;
    while (each)
    {
        Node* next = each->next;
        RenderingUI(renderer, (UI*)each->data);
        each = next;
    }
    each = NULL;
}

void RenderingUI(SDL_Renderer* renderer, UI* ui){
    SDL_Texture* texture = NewTexture(renderer,ui->txt_path);
    RenderingTexture(renderer,texture, ui->position,ui->size);
    SDL_DestroyTexture(texture);
}

void DestroyInterface(Interface* i){
    Node* each = i->UiList->__head;
    while (each)
    {
        Node* next = each->next;
        DestroyUI((UI*)each->data);
        each = next;
    }
    free(each);
    DestroyList(i->UiList);
    free(i);
}

void DestroyUI(UI* ui){
    if(ui){
        DestroyPoint(ui->position);
        DestroySize(ui->size);
        free(ui);
    }
}