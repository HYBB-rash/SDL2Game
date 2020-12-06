//
// Created by hyong on 2020/12/6.
//

#ifndef SDL2GAME_ADT_H
#define SDL2GAME_ADT_H

#include "adt.h"

class LinkNode{
    void *element;
    LinkNode *pre, *nxt;
public:
    void *getElement() const;

    void setElement(void *element);

    LinkNode *getPre() const;

    void setPre(LinkNode *pre);

    LinkNode *getNxt() const;

    void setNxt(LinkNode *nxt);

    void initLinkNode();

    LinkNode* createLinkNode(void* element);


};

class LinkList{

    LinkNode *head, *tail;

public:

    LinkNode *getHead() const;

    void setHead(LinkNode *head);

    LinkNode *getTail() const;

    void setTail(LinkNode *tail);

    void initLinkList();

    static LinkList* createLinkList();

    void destroyLinkList();

    void pushLinkNode(LinkNode* node);

    void pushLinkNodeAtHead(LinkNode* node);

    void removeLinkNode(LinkNode* node);

    void destroyAnimationsByLinkList(LinkList* list);
    void removeAnimationFromLinkList(LinkList* list, Animation* ani);

};



#endif //SDL2GAME_ADT_H
