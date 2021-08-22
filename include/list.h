#ifndef LIST_H
#define LIST_H

#include <common.h>

struct Node{
    void* data;
    struct Node* next;
};

typedef struct Node Node;

typedef struct {
    Node* __head;
    Node* __tail;
} List;

List* NewList();
void DestroyList(List* list);
void AddElemList(List* list, void* elem);

#endif /* LIST_H */