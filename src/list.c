#include "list.h"

List* NewList(){
    List* list = (List*)calloc(1, sizeof(List));
    list->__head = NULL;
    list->__tail = NULL;
    return list;
}

void DestroyList(List* list){
    Node* each = list->__head;
    while (each)
    {
        Node* next = each->next;
        free(each);
        each = next;
    }
    free(list);
}

void AddElemList(List* list, void* elem){
    Node* node = (Node*)calloc(1, sizeof(Node));
    node->data = elem;
    node->next = NULL;
    
    if(list->__head == NULL) {
        list->__head = node;
        list->__tail = node;
    }
    else{
        list->__tail->next = node;
        list->__tail = node;
    }
}