//
// Created by hyong on 2020/12/7.
//

#ifndef SDL2GAME_ADT_H
#define SDL2GAME_ADT_H
class LinkNode {
public:
    void *element;
    LinkNode *pre, *nxt;

    void initLinkNode();
};
class LinkList{
public:
    LinkNode *head, *tail;

    void initLinkList();
    void destroyLinkList();
    void removeAnimationFromLinkList(LinkList* list, Animation* ani);
} ;

void removeLinkNode(LinkList *list ,LinkNode* node);
LinkNode* createLinkNode(void* element);
LinkList* createLinkList();
void destroyAnimationsByLinkList(LinkList* list);
void pushLinkNode(LinkList *list,LinkNode* node);
void pushLinkNodeAtHead(LinkList *list,LinkNode* node);

#endif //SDL2GAME_ADT_H
